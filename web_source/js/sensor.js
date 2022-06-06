/************************* variable *************************/
// sensor element
const lightSensor = document.querySelector('.contents .list li:nth-child(1)');
const temHumSensor = document.querySelector('.contents .list li:nth-child(2)');
const soundSensor = document.querySelector('.contents .list li:nth-child(3)');
const ultraSensor = document.querySelector('.contents .list li:nth-child(4)');
const flameSensor = document.querySelector('.contents .list li:nth-child(5)');
const gasSensor = document.querySelector('.contents .list li:nth-child(6)');
const nearSensor = document.querySelector('.contents .list li:nth-child(7)');

// click element
let click = lightSensor;

// image element
const imageSection = document.querySelector('.contents .right .image img');


/************************* function *************************/
// event-listener function
lightSensor.addEventListener('click', () => {
	click.classList.toggle('click');

	click = lightSensor;
	lightSensor.className = 'click';

	imageSection.setAttribute('src', '../resource/image/sensor/light.png');
});

temHumSensor.addEventListener('click', () => {
	click.classList.toggle('click');

	click = temHumSensor;
	temHumSensor.className = 'click';

	imageSection.setAttribute('src', '../resource/image/sensor/temp-hum.png');
});

soundSensor.addEventListener('click', () => {
	click.classList.toggle('click');

	click = soundSensor;
	soundSensor.className = 'click';
	imageSection.setAttribute('src', '../resource/image/sensor/sound.png');
});

ultraSensor.addEventListener('click', () => {
	click.classList.toggle('click');

	click = ultraSensor;
	ultraSensor.className = 'click';

	imageSection.setAttribute('src', '../resource/image/sensor/ultra.png');
});

flameSensor.addEventListener('click', () => {
	click.classList.toggle('click');

	click = flameSensor;
	flameSensor.className = 'click';

	imageSection.setAttribute('src', '../resource/image/sensor/flame.png');
});

gasSensor.addEventListener('click', () => {
	click.classList.toggle('click');

	click = gasSensor;
	gasSensor.className = 'click';

	imageSection.setAttribute('src', '../resource/image/sensor/gas.png');
});

nearSensor.addEventListener('click', () => {
	click.classList.toggle('click');

	click = nearSensor;
	nearSensor.className = 'click';

	imageSection.setAttribute('src', '../resource/image/sensor/near.png');
});