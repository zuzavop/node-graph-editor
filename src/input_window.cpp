#include "input_window.h"
#include "command.h"

InputWindow::InputWindow() : Window(), _okButton(nullptr), _warning("") {
  _font = std::make_shared<BitmapFont>();
}

InputWindow::~InputWindow() {
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);
}

bool InputWindow::init(const char *name, int width, int height) {
  if (!Window::init(name, 400, 300))
    return false;

  hideWindow();

  if (!_font->buildFont("../data/font.bmp", _window, _renderer)) {
    return false;
  }

  resetInput();
  _okCommand = std::make_shared<OkCommand>(getptr(), nullptr);
  _okButton.reset(new Button(_okCommand, _font, "OK", BIG_FONT_SCALE));
  _okButton->setPosition(_width - (_okButton->getWidth() * BIG_FONT_SCALE) - 10,
                         _height - (_okButton->getHeight() * BIG_FONT_SCALE) -
                             10);

  return true;
}

void InputWindow::setTitle(const std::string &caption) {
  SDL_SetWindowTitle(_window, caption.c_str());
}

void InputWindow::handleEvent(SDL_Event *event) {
  if (event->window.windowID == _id) {
    if (event->type == SDL_TEXTINPUT) {
      _input += event->text.text;
    } else if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
      hideWindow();
    } else if (event->type == SDL_KEYDOWN) {
      if (event->key.keysym.sym == SDLK_DELETE ||
          event->key.keysym.sym == SDLK_BACKSPACE) {
        if (_input.size() > 0) {
          _input.pop_back();
        }
      }
    }
    if (_okButton)
      _okButton->handleEvent(event);
  }
}

void InputWindow::renderWindow() {
  // clear the screen
  SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(_renderer);

  SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);

  _font->renderText(0, 0, _description, _renderer, 0.6);

  _font->renderText(10, 100, _input, _renderer, 0.5);

  if (_okButton)
    _okButton->render(_renderer);

  if (_warning != "") {
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xFF);
    _font->renderText(10, _height - (_font->getWordHeight(_warning) * 0.3) - 10, _warning, _renderer, 0.3, (_width - _okButton->getWidth() - 10) * (1/0.3));
  }

  SDL_RenderPresent(_renderer);
}

void InputWindow::hideWindow() {
  _shown = false;
  _done = false;
  if (_okCommand) _okCommand->getCaller()->isActive(false);
  SDL_HideWindow(_window);
  // disable text input
  SDL_StopTextInput();
}

void InputWindow::setCaller(const std::shared_ptr<PopUpCommand> &caller) {
  _okCommand->setCaller(caller);
}
