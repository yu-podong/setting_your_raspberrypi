/************************* code view function *************************/


/************************* file download function *************************/
function downloadFile() {
	const clickSensor = document.querySelector('.contents .list .click');
	const element = document.createElement('a');
	var fileName = '';
	

	if(clickSensor.classList[0] == 'item1') {
		fileName = 'pumpon.c';
	}
	else if(clickSensor.classList[0] == 'item2') {
		fileName = 'fanon.c';
	}
	else if(clickSensor.classList[0] == 'item3') {
		fileName = 'ledbarsoftpwm.c';
	}
	else if(clickSensor.classList[0] == 'item4') {
		fileName = 'motorsoftpwm.c';
	}
	else if(clickSensor.classList[0] == 'item5') {
		fileName = 'buzcontrol.c';
	}
	else if(clickSensor.classList[0] == 'item6') {
		fileName = 'allrgbcolor.c';
	}
	else if(clickSensor.classList[0] == 'item7') {
		fileName = 'servo.zip';
	}

	// 추후 수정 필요
  element.setAttribute('href',`http://113.198.137.181:2002/web_source/resource/${fileName}`);
  element.setAttribute('download', fileName);
  document.body.appendChild(element);
  element.click();
  //document.body.removeChild(element);
}