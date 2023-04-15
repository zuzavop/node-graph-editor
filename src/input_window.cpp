#include "input_window.h"
#include "main_window.h"
#include "command.h"


InputWindow::InputWindow() : Window(), m_warning(""), m_description(""), m_input(""), m_okButton(nullptr) { 
  m_font = std::make_unique<BitmapFont>();
}

InputWindow::~InputWindow() {
  SDL_DestroyWindow(m_window);
  SDL_DestroyRenderer(m_renderer);
}

bool InputWindow::init(const char *name, int width, int height,
                       bool isResizable, bool isShown) {
  if (!Window::init(name, 400, 300, false, false))
    return false;

  hideWindow();

  if (!m_font->buildFont("../assets/font.bmp", m_window, m_renderer)) {
    return false;
  }

  resetInput();
  m_okButton.reset(new Button(std::make_unique<OkCommand>(nullptr), "OK", BIG_FONT_SCALE));
  m_okButton->setPosition(m_width - m_okButton->getWidth() - PADDING,
                          m_height - m_okButton->getHeight() - PADDING);

  return true;
}

void InputWindow::setTitle(const std::string &caption) {
  SDL_SetWindowTitle(m_window, caption.c_str());
}

void InputWindow::handleEvent(SDL_Event &event) {
  if (event.window.windowID == m_id) {
    if (event.type == SDL_TEXTINPUT) {
      m_input += event.text.text;
    } else if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
      hideWindow();
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_DELETE ||
          event.key.keysym.sym == SDLK_BACKSPACE) {
        if (m_input.size() > 0) {
          m_input.pop_back();
        }
      }
    }
    if (m_okButton)
      m_okButton->handleEvent(event);
  }
}

void InputWindow::renderWindow() {
  // clear the screen
  SDL_SetRenderDrawColor(m_renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
  SDL_RenderClear(m_renderer);

  SDL_SetRenderDrawColor(m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);

  if (!m_description.empty()) m_font->renderText(0, 0, m_description, m_renderer, NORMAL_FONT_SCALE);

  if (!m_input.empty()) m_font->renderText(INPUT_START_X, INPUT_START_Y, m_input, m_renderer, FONT_SCALE);

  if (m_okButton)
    m_okButton->render(m_renderer, m_font);

  if (!m_warning.empty()) {
    SDL_SetRenderDrawColor(m_renderer, RED.r, RED.g, RED.b, RED.a);
    // scale position and size
    float y = m_height - (m_font->getWordHeight(m_warning) * SMALL_FONT_SCALE) -
              PADDING;
    float maxWidth =
        (m_width - ((m_okButton ? m_okButton->getWidth() : BUTTON_WIDTH) * (1 / BIG_FONT_SCALE)) - PADDING) *
        (1 / SMALL_FONT_SCALE);
    m_font->renderText(INPUT_START_X, y, m_warning, m_renderer, SMALL_FONT_SCALE, maxWidth);
  }

  SDL_RenderPresent(m_renderer);
}

void InputWindow::hideWindow() {
  m_shown = false;
  m_done = false;
  SDL_HideWindow(m_window);
  SDL_StopTextInput();
}

void InputWindow::setCaller(PopUpCommand *caller) {
  if (m_okButton)
    dynamic_cast<OkCommand*>(m_okButton->function.get())->setCaller(caller);
}
