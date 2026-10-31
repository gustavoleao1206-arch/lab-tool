#pragma once
// ============================================================================
// Interface comum de um "app" do dispositivo. Tudo que aparece no menu
// implementa esta interface -> o nucleo (Menu) nao precisa conhecer os apps.
//
//   enter(cfg)  -> chamado 1x ao abrir o app (aloca recursos)
//   loop(...)   -> chamado a cada frame enquanto o app esta ativo
//   exit()      -> chamado 1x ao fechar (libera recursos)
//   sair()      -> o app chama para pedir para voltar ao menu
// ============================================================================
class Buttons;
class Display;
class Config;

class App {
public:
  virtual ~App() {}
  virtual const char* nome() const = 0;
  virtual void enter(Config& cfg) { (void)cfg; }
  virtual void loop(Buttons& btn, Display& disp, Config& cfg) = 0;
  virtual void exit() {}

  bool querSair() const { return sair_; }
  void limparSair()     { sair_ = false; }

protected:
  void sair() { sair_ = true; }
  bool sair_ = false;
};
