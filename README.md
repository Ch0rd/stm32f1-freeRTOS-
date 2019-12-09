stm32f1-FreeRTOS
学习开发项目框架


作者：chord


简介：此项目是搭载在stm32f1上的FreeRTOS开发项目框架。大体开发框架已调试完成，后续更新逐渐添加新功能，添加学习工具方便学习使用。自行添加具体的硬件驱动、动作逻辑可直接用于设计开发。


·通讯使用串口收发，通过消息队列完成接受、发送任务间数据传输
·动作任务开启使用二值信号量控制，串口接受指令解析，正确指令传递信号量开启动作任务
·项目中简单的通讯协议近似于modbus，可自行修改，也可移植modbus通讯协议。
·作为从机使用接受上位机命令并应答，也可通过修改串口使用逻辑与通讯协议开发主机。


项目功能并不复杂，是以简单、易学习为目标而编写的小项目.
