#ifndef INPUT_WINDOW_H
#define INPUT_WINDOW_H

#include "button.h"
#include "window.h"

class InputWindow : public Window,
                    public std::enable_shared_from_this<InputWindow> {
public:
  InputWindow();
  ~InputWindow();

  bool init(const char *name, int width = WINDOW_WIDTH,
            int height = WINDOW_HEIGHT) override;

  void setDescription(const std::string description) {
    _description = description;
  }
  void setTitle(const std::string &caption);
  void setCaller(const std::shared_ptr<PopUpCommand> &caller);

  void mainLoop() override{};
  void handleEvent(SDL_Event *event);
  void renderWindow() override;
  void resetInput(const std::string & input = "") { _input = input; }
  void hideWindow();

  const std::string &getInput() { return _input; }
  std::shared_ptr<InputWindow> getptr() { return shared_from_this(); }
  bool isActive() { return _shown; }

private:
  std::shared_ptr<BitmapFont> _font;
  std::string _input;
  std::string _description;
  std::unique_ptr<Button> _okButton;
  std::shared_ptr<OkCommand> _okCommand;
};

#endif
