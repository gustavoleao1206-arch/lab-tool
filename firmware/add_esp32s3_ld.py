# Workaround para espressif32@8.0.0:
# adiciona ao caminho de busca do linker os diretorios de linker scripts dos
# libs pre-compilados do ESP32-S3 (sem isso o link falha com
# "cannot open linker script file ...ld"). Dois diretorios sao necessarios:
#   <libs>/ld            -> memory.ld, peripherals.ld, rom.*.ld
#   <libs>/<memory_type> -> sections.ld (depende de flash/PSRAM)
# No Windows usa o caminho curto 8.3 (evita espaco/acento no dir do usuario).
Import("env")  # noqa: F821
import os


def short_path(p):
    try:
        import ctypes
        buf = ctypes.create_unicode_buffer(1024)
        if ctypes.windll.kernel32.GetShortPathNameW(p, buf, 1024):
            return buf.value
    except Exception:
        pass
    return p


# localizar o pacote de libs do ESP32-S3
libs = None
try:
    libs = env.PioPlatform().get_package_dir("framework-arduinoespressif32-esp32s3-libs")
except Exception:
    libs = None
if not libs:
    libs = os.path.join(env.subst("$PROJECT_PACKAGES_DIR"),
                        "framework-arduinoespressif32-esp32s3-libs")


def add_ld(d):
    if d and os.path.isdir(d):
        sp = short_path(d)
        env.Append(LIBPATH=[sp])
        env.Append(LINKFLAGS=["-L" + sp])
        print(">>> [ld-workaround] -L", sp)
        return True
    return False


add_ld(os.path.join(libs, "ld"))

mem = env.BoardConfig().get("build.arduino.memory_type", "") or "qio_qspi"
print(">>> [ld-workaround] memory_type =", mem)
if not add_ld(os.path.join(libs, mem)):
    add_ld(os.path.join(libs, "qio_qspi"))


# O ld.exe nao abre caminho absoluto com acento (ex.: "Leao" -> mojibake) para
# criar o firmware.map. O .map e so diagnostico e nao entra no .bin, entao
# removemos o -Map do link para que o projeto compile em qualquer pasta.
# O framework (platformio-build.py) adiciona dois tokens em LINKFLAGS:
#   "-Wl,--Map"  seguido do caminho "<BUILD_DIR>/${PROGNAME}.map"
def _drop_map(flags):
    out = []
    skip_next = False
    for f in flags:
        if skip_next:
            skip_next = False
            continue
        s = str(f)
        if "-Map" in s:                 # -Wl,--Map / -Wl,-Map / -Map(=...)
            if "=" not in s:            # caminho vem no proximo token
                skip_next = True
            continue
        if s.endswith(".map"):          # token de caminho do .map
            continue
        out.append(f)
    return out


env.Replace(LINKFLAGS=_drop_map(env.get("LINKFLAGS", [])))
