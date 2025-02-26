nrTotalBaloaneSparte = 0

if (!localStorage.getItem('nrTotalBaloaneSparte')) {
    localStorage.setItem('nrTotalBaloaneSparte', '0');
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
    contor.innerText = `Numarul total de baloane sparte este: ${nrTotalBaloaneSparte}`
}

ballons = []

document.body.onkeydown = (e) => {
    if(e.key === 'b'){
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
        ballon.style.backgroundImage = "url(resources/images/ballon.png)"
        ballons.push(ballon)
        ballon.onclick = spart
        

        function spart(){
            ballon.style.backgroundImage = "url(resources/images/pow.png)"
            incBaloaneSparte()
            setTimeout(() => {
                removeBallon(ballon)
            }, 300)
            let cantec = Math.floor(Math.random()*3+1)
            let sunet = document.createElement('audio')
            sunet.src = `resources/sounds/pop-${cantec}.mp3`
            document.body.append(sunet)
            sunet.play()

            }
        

        document.body.append(ballon)
    }
    if(e.key === 'p'){
        if(movingUp) return
        movingUp = true;
        requestAnimationFrame(moveUp)
    }    
    if(e.key === 'f'){
        movingUp = false;
    }
}

function removeBallon(ballon){
    var i  = ballons.indexOf(ballon)
    if(i >= 0)
        ballons.splice(i, 1)
    ballon.remove()
}

var lastTimestamp = -1;
var movingUp = false;
function moveUp(timestamp) {
    if(movingUp == false){
        lastTimestamp = -1;
        return;
    }

    if(lastTimestamp == -1){
        lastTimestamp = timestamp;
    }

    var deltaTime = timestamp - lastTimestamp;

    for(let i = 0; i < ballons.length; i++){
        var prevPos = parseFloat(ballons[i].style.top.slice(0, -2));


        var speed = 0.25;
        prevPos -= deltaTime * speed;

        if(prevPos < -500){
            removeBallon(ballons[i])
            i--;
            continue;
        } 

        ballons[i].style.top = `${prevPos}px`
    }

    lastTimestamp = timestamp;

    requestAnimationFrame(moveUp)
}