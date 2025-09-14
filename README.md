# Clock
## Introduction
This is a simple clock for everyone to use.
This clock is not a professional work, only a learner's test work.
I won't promise to keep upholding this project. But I will update if I find something new.
## How to use
**R** for reset  
**P** for pause  
**A**/**D**/**<-**/**->** for changing input cursor  
**M** for changing counting mode  
+ COUNT UP
+ COUNT DOWN
## The lib I have used
[EasyX](https://easyx.cn/)  
A graphic library for C++,which helps me escape from boring coding of graphic handle.
## Future plan
+ add config file to save the setting or to change the style of the clock
+ make its size changeable
+ add setting page
+ add real time mode
+ what else...
## File structure
```
-Clock  
|Cpp  
|-main.cpp  
|-Interaction.cpp  \\for coping with the keyboard input
|-Logic.cpp  \\main logic for the clock
|-Display.cpp  \\for displaying the clock
|Header  
|-Display.h
|-Logic.h
|-Interaction.h
|-Timer.h
```
