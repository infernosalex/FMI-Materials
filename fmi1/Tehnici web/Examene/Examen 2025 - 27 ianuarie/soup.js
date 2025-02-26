nrTotalBaloaneSparte = 0

if (!sessionStorage.getItem('nrTotalBaloaneSparte')) {
    sessionStorage.setItem('nrTotalBaloaneSparte', '0');
}


let contor = document.createElement('div')
contor.innerText = `Numarul total de baloane sparte este: ${nrTotalBaloaneSparte}`
contor.style.right='10px'
contor.style.padding = '5px'
contor.style.backgroundColor = "white"
contor.style.position="absolute"
contor.style.zIndex = 100000
document.body.append(contor)

function incBaloaneSparte(){
    nrTotalBaloaneSparte++
    sessionStorage.setItem('nrTotalBaloaneSparte', '0');
    contor.innerText = `Numarul total de baloane sparte este: ${nrTotalBaloaneSparte}`
}

ballons = []

document.body.onkeydown = (e) => {
    if(e.key === 's'){
        let ballon = document.createElement('div')
        let x = Math.random() * (window.innerWidth - 100)
        let y = Math.random() * (window.innerHeight - 100)

        ballon.style.top = y+"px"
        ballon.style.left = x+"px"
        ballon.style.width = "100px"
        ballon.style.height = "100px"
        ballon.style.position = "absolute"
        ballon.className = "ballon"
        ballon.style.backgroundSize = "contain"
        ballon.style.backgroundRepeat = "no-repeat"
        ballon.style.backgroundImage = "url(resources/images/bubble-1.png)"
        ballon.angle = Math.random() * Math.PI
        ballons.push(ballon)
        ballon.onclick = spart
        
        let bubbles = ["url(resources/images/bubble-2.png)","url(resources/images/bubble-3.png)","url(resources/images/bubble-4.png)"]
        let isClicked = false
        function spart(){
            if(!isClicked){
                isClicked = true
                for(let i=0;i<3;i++){
                    setTimeout(() => {
                        ballon.style.backgroundImage = bubbles[i] 
                    }, i*200)
                }
                setTimeout(() => {
                    incBaloaneSparte()
                    removeBallon(ballon)
                    isClicked = false
                }, 600)     
            }
        }
        document.body.append(ballon)
    }
    if(e.key === 'p'){
        if(movingAllDirection) return
        movingAllDirection = true;
        requestAnimationFrame(moveAllDirections)
    }    
    if(e.key === 'f'){
        movingAllDirection = false;
    }
}

function removeBallon(ballon){
    var i  = ballons.indexOf(ballon)
    if(i >= 0)
        ballons.splice(i, 1)
    ballon.remove()
}

var lastTimestamp = -1;
var movingAllDirection = false;

function moveAllDirections(timestamp) {
    if(movingAllDirection == false){
        lastTimestamp = -1;
        return;
    }

    if(lastTimestamp == -1){
        lastTimestamp = timestamp;
    }

    var deltaTime = timestamp - lastTimestamp;

    for(let i = 0; i < ballons.length; i++){
        var directionChangeSpeed = 50;
        ballons[i].angle += (Math.random() * directionChangeSpeed - directionChangeSpeed / 2) * (deltaTime / 1000);

        var posX = parseFloat(ballons[i].style.left.slice(0, -2));
        var posY = parseFloat(ballons[i].style.top.slice(0, -2));

        var speed = 0.05;
        posX += Math.cos(ballons[i].angle) * speed * deltaTime;
        posY += Math.sin(ballons[i].angle) * speed * deltaTime;
        
        ballons[i].style.top = `${posY}px`;
        ballons[i].style.left = `${posX}px`;
    }

    lastTimestamp = timestamp;

    requestAnimationFrame(moveAllDirections)
}