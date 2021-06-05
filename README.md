# rtSolder

As I have the full Weller power for business I wanted to have a cheap solution to work with Wellers RT solder tips at home. Small package, a wide input voltage range, simple to use and scaleable power consumption have been targets of my project.
Final solution is a microchip PIC controller, reading the temperature signal which is processed by a TLV333 op amp, controlling a step down converter to regulate temperature and also drive the display.
Output power is adjustable in 10W steps from 10W to 40W. In 10W mode its also possible to use USB power. For higher power a higher voltage is necessary. Voltage maximum is 30V. 
