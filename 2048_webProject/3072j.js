var score = 0;  //스코어 변수

//이름 입력받기
function nameSet(){  
	name = $('input[userName]').val();
}

var game = new Array(4);		//게임 맵   저장
var undoTmp = new Array(4);	//지난 위치 저장

//2차원 배열 생성
for(var i=0;i<game.length;i++){
	game[i] = new Array(4);
	undoTmp[i] = new Array(4);
}

function gameOverHidden(){
	$('form').append('<input type="hidden" name="score" value="'+score+'"/>');	
}

//키눌렀을때 스크롤이 내려가지않게
jQuery(document).keydown(function(e) {	
	if(e.target.nodeName != "INPUT" && e.target.nodeName != "TEXTAREA") {
		if(e.keyCode === 37 || e.keyCode === 38 || e.keyCode === 39 || e.keyCode === 40) {
			return false;
		}
	}
});

//새로고침시 디자인 맞춤
function resize() {
	$('#main').css('width', $(window).width());
	$('#main').css('height', $(window).height());
}

//onload function  ------------------------
$(window).resize(resize());
$(function(){
	start();
});
$(function(){
	$('#undo').click(function() {
		for(var i=0;i<4;i++){
			for(var j=0;j<4;j++){
				game[i][j] = undoTmp[i][j];	
			}
		}
		Change();
	});
});

//undo function ---------------------------
function undoSave() {
	for(var i=0;i<4;i++){
		for(var j=0;j<4;j++){
			undoTmp[i][j] = game[i][j];	
		}
	}
}

//게임 시작과 순서 ------------------------
function start() {
	$('#main').css('width', "100%");
	$('#main').css('height', $(window).height());
	
	var rand1 = Math.floor(Math.random()*2);
	var randTmp1 = rand1==0?3:6;
	var rand2 = Math.floor(Math.random()*2);
	var randTmp2 = rand2==0?3:6;
	
	var randP1 = Math.floor(Math.random()*16);
	var randP2 = Math.floor(Math.random()*16);
	
	while(true){
		if(randP1 == randP2){
			randP2 = Math.floor(Math.random()*16);	
			continue;
		}
		break;
	}
	for(var i=0;i<4;i++){
		for(var j=0;j<4;j++){
			game[i][j] = 0;
		}
	}
	
	for(var i=0;i<16;i++){
		if(randP1==i){
			game[Math.floor(i/4)][i%4] = randTmp1;
		}
		if(randP2==i){
			game[Math.floor(i/4)][i%4] = randTmp2;
		}
	}
	undoSave();
	for(var i=0;i<16;i++){
		$('#board').append('<div class="block" id="'+i+'">'+game[Math.floor(i/4)][i%4]+'</div>');
		
		/*'*/
		
		if(i%4==3){
			$('#board').append('<div style="clear:both"></div>');
		}
	}
	Change();
}

//블럭 랜덤생성 --------------------------------
function randCre() {
	var array = new Array();
	var cnt = 0;
	for(var i=0;i<4;i++){
		for(var j=0;j<4;j++){
			if(game[i][j] == 0){
				array[cnt] = i+"-"+j;
				cnt++;
			}
		}
	}
	var noGameOverCnt=0;
	if(cnt == 0){
		for(var i=1;i<4;i++){
			for(var j=1;j<4;j++){
				if(game[i][j]==game[i-1][j] || game[i][j]==game[i][j-1]) {
					noGameOverCnt++;
				}
			}
		}
		if(noGameOverCnt==0){
			gameOver();	
			gameOverHidden();
		}
	}else{
		var cRand = Math.floor(Math.random()*cnt);
		var spTmp = array[cRand].split("-");
		var rand1 = Math.floor(Math.random()*2);
		var randTmp = rand1==0?3:6;
		
		score += randTmp*2;//스코어
		
		game[spTmp[0]][spTmp[1]] = randTmp;
	}
}

//키코드 입력받기 ------------------------
function key_down() {
	var result = true;
    var keycode = event.keyCode;
	var nTmp;
	undoSave();
	if(event.keyCode == 37){  //왼쪽
		for (i = 0; i < 4; i++) {
			for (k = 0; k < 4; k++) {
				for (j = 1; j < 4; j++) {
					if (game[i][j - 1] == 0) {
						game[i][j - 1] = game[i][j];
						game[i][j] = 0;
					}
				}
			}
			for (j = 1; j < 4; j++) {
				if (game[i][j - 1] == game[i][j]) {
					game[i][j - 1] += game[i][j];
					game[i][j] = 0;
				}
			}
			for (k = 0; k < 4; k++) {
				for (j = 1; j < 4; j++) {
					if (game[i][j - 1] == 0) {
						game[i][j - 1] = game[i][j];
						game[i][j] = 0;
					}
				}
			}
		}
	}
	else if(event.keyCode == 38){  //위
		for (i = 0; i < 4; i++) {
			for (k = 0; k < 4; k++) {
				for (j = 1; j < 4; j++) {
					if (game[j - 1][i] == 0) {
						game[j - 1][i] = game[j][i];
						game[j][i] = 0;
					}
				}
			}
			for (j = 1; j < 4; j++) {
				if (game[j - 1][i] == game[j][i]) {
					game[j - 1][i] += game[j][i];
					game[j][i] = 0;
				}
			}
			for (k = 0; k < 4; k++) {
				for (j = 1; j < 4; j++) {
					if (game[j - 1][i] == 0) {
						game[j - 1][i] = game[j][i];
						game[j][i] = 0;
					}
				}
			}
		}
	}
	else if(event.keyCode == 39){  //오른쪽
		for (i = 0; i < 4; i++) {
			for (k = 0; k < 4; k++) {
				for (j = 2; j >= 0; j--) {
					if (game[i][j + 1] == 0) {
						game[i][j + 1] = game[i][j];
						game[i][j] = 0;
					}
				}
			}
			for (j = 2; j >= 0; j--) {
				if (game[i][j + 1] == game[i][j]) {
					game[i][j + 1] += game[i][j];
					game[i][j] = 0;
				}
			}
			for (k = 0; k < 4; k++) {
				for (j = 2; j >= 0; j--) {
					if (game[i][j + 1] == 0) {
						game[i][j + 1] = game[i][j];
						game[i][j] = 0;
					}
				}
			}
		}
	}
	else if(event.keyCode == 40){  //아레
		for (i = 0; i < 4; i++) {
			for (k = 0; k < 4; k++) {
				for (j = 2; j >= 0; j--) {
					if (game[j + 1][i] == 0) {
						game[j + 1][i] = game[j][i];
						game[j][i] = 0;
					}
				}
			}
			for (j = 2; j >= 0; j--) {
				if (game[j + 1][i] == game[j][i]) {
					game[j + 1][i] += game[j][i];
					game[j][i] = 0;
				}
			}
			for (k = 0; k < 4; k++) {
				for (j = 2; j >= 0; j--) {
					if (game[j + 1][i] == 0) {
						game[j + 1][i] = game[j][i];
						game[j][i] = 0;
					}
				}
			}
		}
	}
	else{
		return;
	}
	randCre();
	Change();
	fScore();
}

//스코어 보여주기
function fScore() {
	$('#score').html(score);
}

//게임 오버 창띄우기
function gameOver(){
	$('#gameOver').css("display","block");
}

//숫자에 따라서 색 바꿔주기
function Change(){
	for(var i=0;i<16;i++){
		var color;
		var fontColor="#555";
		var cTmp = game[Math.floor(i/4)][i%4];
		if(cTmp>=384){
			fontColor="#ADADAD";
		}
		switch(cTmp){
			case 0:
				color = "#FFF";
				break;
			case 3:
				color = "#EEE";
				break;
			case 6:
				color = "#DDD";
				break;
			case 12:
				color = "#CCC";
				break;
			case 24:
				color = "#BBB";
				break;
			case 48:
				color = "#AAA";
				break;
			case 96:
				color = "#999";
				break;
			case 192:
				color = "#888";
				break;
			case 384:
				color = "#777";
				break;
			case 768:
				color = "#666";
				break;
			case 1536:
				color = "#555";
				break;
			case 3072:
				color = "#444";
				break;
			case 6144:
				color = "#333";
				break;
			case 12288:
				color = "#222";
				break;
			case 24576:
				color = "#111";
				break;
			case 49152:
				color = "#000";
				break;
			case 98304:
				color = "linear-gradient(to bottom, #cfe7fa 0%,#6393c1 100%)";
				break;
			case 196608:
				color = "linear-gradient(to bottom, #f6e6b4 11%,#ed9017 100%)";
				break;
		}
		$('#'+i).css("color",fontColor);
		$('#'+i).css("background",color);
		$('#'+i).html(game[Math.floor(i/4)][i%4]==0?"":game[Math.floor(i/4)][i%4]);
	}
}
function go(){
    window.location.reload();
}