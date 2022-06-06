/************************* variable *************************/
// sensor element
const pump = document.querySelector('.contents .list li:nth-child(1)');
const fan = document.querySelector('.contents .list li:nth-child(2)');
const led = document.querySelector('.contents .list li:nth-child(3)');
const motor = document.querySelector('.contents .list li:nth-child(4)');
const buzzer = document.querySelector('.contents .list li:nth-child(5)');
const rgbLed = document.querySelector('.contents .list li:nth-child(6)');
const servo = document.querySelector('.contents .list li:nth-child(7)');

// click element
let click = pump;

// image element
const imageSection = document.querySelector('.contents .right .image img');


/************************* function *************************/
// event-listener function
pump.addEventListener('click', () => {
	click.classList.toggle('click');

	click = pump;
	pump.className = 'click';

	imageSection.setAttribute('src', '../resource/image/actuator/pump.png');
});

fan.addEventListener('click', () => {
	click.classList.toggle('click');

	click = fan;
	fan.className = 'click';

	imageSection.setAttribute('src', '../resource/image/actuator/fan.png');
});

led.addEventListener('click', () => {
	click.classList.toggle('click');

	click = led;
	led.className = 'click';

	imageSection.setAttribute('src', '../resource/image/actuator/led-bar.png');
});

motor.addEventListener('click', () => {
	click.classList.toggle('click');

	click = motor;
	motor.className = 'click';

	imageSection.setAttribute('src', '../resource/image/actuator/motor.png');
});

buzzer.addEventListener('click', () => {
	click.classList.toggle('click');

	click = buzzer;
	buzzer.className = 'click';

	imageSection.setAttribute('src', '../resource/image/actuator/buzzer.png');
});

rgbLed.addEventListener('click', () => {
	click.classList.toggle('click');

	click = rgbLed;
	rgbLed.className = 'click';

	imageSection.setAttribute('src', '../resource/image/actuator/rgb-led.png');
});

servo.addEventListener('click', () => {
	click.classList.toggle('click');

	click = servo;
	servo.className = 'click';

	imageSection.setAttribute('src', '../resource/image/actuator/servo-motor.png');
});