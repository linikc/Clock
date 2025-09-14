#include "Interaction.h"

void Interaction::GetInput(ExMessage msg) {
    peekmessage(&msg, EX_KEY);
    if (msg.message == WM_KEYDOWN) {
        Key = msg;
    }
    else
        Key.vkcode = NULL;
    return;
}

InputState Interaction::GetInputState() {
    return input_state;
}

TimerMode Interaction::GetTimerMode() {
    return Mode;
}

void Interaction::HandleInputA() {
    Time = 0;
    if (Key.vkcode >= '0' && Key.vkcode <= '9') {
        Num = (char)Key.vkcode;
        if (Input.length() < 2) {
            Input += Num;
            Time = std::stoi(Input);
        }
    }
    switch (Key.vkcode)
    {
    case VK_BACK:
        Time = CLEAN;
        printf("BACK");
        return;
    case 68:
    case VK_RIGHT:
        Time = 0;
        input_state = (InputState)((input_state + 1) % 3);
        Input = "";
        return;
    case 65:
    case VK_LEFT:
        Time = 0;
        input_state = (InputState)((input_state + 2) % 3);
        Input = "";
        return;
    default:
        break;
    }
    if (input_state == SEC && Input.length() == 2) {
        Status = RUN;
        input_state = HOR;
        Input = "";
    }
}

void Interaction::HandleInputB() {
    if (Key.vkcode == 80)
    {
        if (Status == RUN) {
            Status = STOP;
        }
        else if (Status == STOP) {
            Status = RUN;
        }
    }
    if (Key.vkcode == 82) {
        Status = RESET;
    }
    if (Key.vkcode == VK_ESCAPE || Key.vkcode == 88)
        Status = EXIT;
}

void Interaction::HandleModeChange() {
    if (Key.vkcode == 77) {
        Mode = (TimerMode)((Mode + 1) % 2);
    }
    if (Key.vkcode == VK_RETURN&&Status == START) {
            Status = RUN;
            input_state = HOR;
            Time = 0;
            Input = "";
            return;
    }
}

void Interaction::ReturnInput(int& time) {
    if (Time == CLEAN) {
        Time = 0;
        time = 0;
        Input = "";
        return;
    }
    if (Time == 0&&time != 0) {
        time = time; return;
    }
    time = Time;
}
