#ifndef INPUT_WINDOW_H
#define INPUT_WINDOW_H

#include "button.h"
#include "window.h"

class InputWindow : public Window,
                    public std::enable_shared_from_this<InputWindow> {
public:
  InputWindow();
  ~InputWindow();

  bool init(const char *name = "", int width = WINDOW_WIDTH,
            int height = WINDOW_HEIGHT, bool isResizable = true,
            bool isShown = true) override;

  void setDescription(std::string description) { m_description = description; }
  void setWarning(std::string warning = "") { m_warning = warning; }
  void setTitle(const std::string &caption);
  void setCaller(std::shared_ptr<PopUpCommand> caller);

  void mainLoop() override{};
  void handleEvent(SDL_Event &event);
  void renderWindow() override;
  void resetInput(const std::string &input = "") { m_input = input; }
  void hideWindow();
  void doneInput(bool isDone = true) { m_done = isDone; }

  const std::string &getInput() const { return m_input; }
  std::shared_ptr<InputWindow> getPtr() { return shared_from_this(); }
  bool isActive() const { return !m_done; }

private:
  std::shared_ptr<BitmapFont> m_font;
  std::string m_input;
  std::string m_description;
  std::string m_warning;
  std::unique_ptr<Button> m_okButton;
  std::shared_ptr<OkCommand> m_okCommand;
  bool m_done;
};

#endif
