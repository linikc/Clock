#include "Interaction.h"

int Interaction::GetInput() {
    Key = 0;
    if (_kbhit())
        Key = _getch();
    return Key;
}

InputState Interaction::GetInputState() {
    return input_state;
}

void Interaction::HandleInputA() {
    Time = 0;
    if (Key >= '0' && Key <= '9') {
        Num = (char)Key;
        if (Input.length() < 2) {
            Input += Num;
            Time = std::stoi(Input);
        }
    }
    if (Key == 8) {
        Time = 0;
        Input = "";
    }
    if (Key == 'd' || Key == 77){
        input_state = (InputState)((input_state + 1) % 3);
        Input = "";
        printf("->\n");
    }
    if (Key == 'a' || Key == 75){
        input_state = (InputState)((input_state + 2) % 3);
        Input = "";
        printf("<-\n");
    }
    if (Key == 13) {
        Status = RUN;
        input_state = HOR;
        Input = "";
        Time = 0;
        return;
    }
    if (input_state == SEC && Input.length() == 2) {
        Status = RUN;
        input_state = HOR;
        Input = "";
    }
}

void Interaction::HandleInputB() {
    if (Key == 'q')
    {
        if (Status == RUN) {
            Status = STOP;
        }
        else if (Status == STOP) {
            Status = RUN;
        }     
    }
    if (Key == 'r')
        Status = RESET;
}

void Interaction::ReturnInput(int& time) {
    time = Time;
}
