// LAF OS Library
// Copyright (C) 2019  Igara Studio S.A.
// Copyright (C) 2012-2018  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef OS_EVENT_H_INCLUDED
#define OS_EVENT_H_INCLUDED
#pragma once

#include "base/paths.h"
#include "gfx/point.h"
#include "gfx/size.h"
#include "os/keys.h"
#include "os/pointer_type.h"

#include <functional>

#pragma push_macro("None")
#undef None // Undefine the X11 None macro

namespace os {

  class Display;

  class Event {
  public:
    enum Type {
      None,
      CloseDisplay,
      ResizeDisplay,
      DropFiles,
      MouseEnter,
      MouseLeave,
      MouseMove,
      MouseDown,
      MouseUp,
      MouseWheel,
      MouseDoubleClick,
      KeyDown,
      KeyUp,
      TouchMagnify,
      Callback,
    };

    enum MouseButton {
      NoneButton,
      LeftButton,
      RightButton,
      MiddleButton,
      X1Button,
      X2Button,
    };

    Event() : m_type(None),
              m_display(nullptr),
              m_scancode(kKeyNil),
              m_modifiers(kKeyUninitializedModifier),
              m_unicodeChar(0),
              m_isDead(false),
              m_repeat(0),
              m_preciseWheel(false),
              m_pointerType(PointerType::Unknown),
              m_button(NoneButton),
              m_magnification(0.0),
              m_pressure(0.0) {
    }

    Type type() const { return m_type; }
    Display* display() const { return m_display; }
    const base::paths& files() const { return m_files; }
    // TODO Rename this to virtualKey(), which is the real
    // meaning. Then we need another kind of "scan code" with the
    // position in the keyboard, which might be useful to identify
    // keys by its position (e.g. WASD keys in other keyboard
    // layouts).
    KeyScancode scancode() const { return m_scancode; }
    KeyModifiers modifiers() const { return m_modifiers; }
    int unicodeChar() const { return m_unicodeChar; }
    bool isDeadKey() const { return m_isDead; }
    int repeat() const { return m_repeat; }
    gfx::Point position() const { return m_position; }
    gfx::Point wheelDelta() const { return m_wheelDelta; }

    // We suppose that if we are receiving precise scrolling deltas,
    // it means that the user is using a touch-like surface (trackpad,
    // magic mouse scrolling, touch wacom tablet, etc.)
    bool preciseWheel() const { return m_preciseWheel; }

    PointerType pointerType() const { return m_pointerType; }
    MouseButton button() const { return m_button; }
    double magnification() const { return m_magnification; }
    double pressure() const { return m_pressure; }

    void setType(Type type) { m_type = type; }
    void setDisplay(Display* display) { m_display = display; }
    void setFiles(const base::paths& files) { m_files = files; }
    void setCallback(std::function<void()>&& func) { m_callback = std::move(func); }

    void setScancode(KeyScancode scancode) { m_scancode = scancode; }
    void setModifiers(KeyModifiers modifiers) { m_modifiers = modifiers; }
    void setUnicodeChar(int unicodeChar) { m_unicodeChar = unicodeChar; }
    void setDeadKey(bool state) { m_isDead = state; }
    void setRepeat(int repeat) { m_repeat = repeat; }
    void setPosition(const gfx::Point& pos) { m_position = pos; }
    void setWheelDelta(const gfx::Point& delta) { m_wheelDelta = delta; }
    void setPreciseWheel(bool precise) { m_preciseWheel = precise; }
    void setPointerType(PointerType pointerType) { m_pointerType = pointerType; }
    void setButton(MouseButton button) { m_button = button; }
    void setMagnification(double magnification) { m_magnification = magnification; }
    void setPressure(double pressure) { m_pressure = pressure; }

    void execCallback() { if (m_callback) m_callback(); }

  private:
    Type m_type;
    Display* m_display;
    base::paths m_files;
    std::function<void()> m_callback;
    KeyScancode m_scancode;
    KeyModifiers m_modifiers;
    int m_unicodeChar;
    bool m_isDead;
    int m_repeat; // repeat=0 means the first time the key is pressed
    gfx::Point m_position;
    gfx::Point m_wheelDelta;
    bool m_preciseWheel;
    PointerType m_pointerType;
    MouseButton m_button;

    // For TouchMagnify event
    double m_magnification;

    // Pressure of stylus used in mouse-like events
    double m_pressure;
  };

} // namespace os

#pragma pop_macro("None")

#endif