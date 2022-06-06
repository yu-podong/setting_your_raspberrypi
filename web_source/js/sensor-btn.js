/************************* help function *************************/


/************************* code view function *************************/

/************************* file download function *************************/
function downloadFile() {
	const clickSensor = document.querySelector('.contents .list .click');
	const element = document.createElement('a');
	var fileName = '';
	

	if(clickSensor.classList[0] == 'item1') {
		fileName = 'getlightsensor.c';
	}
	else if(clickSensor.classList[0] == 'item2') {
		fileName = 'get-numitemp.c';
	}
	else if(clickSensor.classList[0] == 'item3') {
		fileName = 'soundtest.c';
	}
	else if(clickSensor.classList[0] == 'item4') {
		fileName = 'ultrasonic.c';
	}
	else if(clickSensor.classList[0] == 'item5') {
		fileName = 'flame.c';
	}
	else if(clickSensor.classList[0] == 'item6') {
		fileName = 'gasdetect.c';
	}
	else if(clickSensor.classList[0] == 'item7') {
		fileName = 'neardetect.c';
	}

	// 추후 수정 필요
  element.setAttribute('href',`http://113.198.137.181:2002/web_source/resource/${fileName}`);
  element.setAttribute('download', fileName);
  document.body.appendChild(element);
  element.click();
  //document.body.removeChild(element);
}