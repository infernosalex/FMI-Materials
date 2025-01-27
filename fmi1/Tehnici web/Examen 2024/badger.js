nrTotalGenoflexiuni = 0

if (!localStorage.getItem('nrTotalGenoflexiuni')) {
    localStorage.setItem('nrTotalGenoflexiuni', '0');
}


let contor = document.createElement('div')
contor.innerText = `Numarul total de genoflexiuni este: ${nrTotalGenoflexiuni}`
contor.style.right='10px'
contor.style.padding = '5px'
contor.style.backgroundColor = "white"
contor.style.position="absolute"
contor.style.zIndex = 100000
document.body.append(contor)

function incGenoflexiuni(){
    nrTotalGenoflexiuni++
    contor.innerText = `Numarul total de genoflexiuni este: ${nrTotalGenoflexiuni}`

    if(nrTotalGenoflexiuni % 5 == 0 && nrTotalGenoflexiuni != 0){
        let ciuperca = document.createElement('div')
        let x = Math.random() * (window.innerWidth - 100)
        let y = Math.random() * (window.innerHeight - 100)

        ciuperca.style.top = y+"px"
        ciuperca.style.left = x+"px"
        ciuperca.style.width = "100px"
        ciuperca.style.height = "100px"
        ciuperca.style.position = "absolute"
        ciuperca.style.backgroundSize = "contain"
        ciuperca.style.backgroundImage = "url(resources/images/mush.png)"

        document.body.append(ciuperca)
    }

}

document.body.onkeydown = (e) => {
    if(e.key === 'b'){
        let bursucNou = document.createElement('div')
        let x = Math.random() * (window.innerWidth - 100)
        let y = Math.random() * (window.innerHeight - 100)

        bursucNou.style.top = y+"px"
        bursucNou.style.left = x+"px"
        bursucNou.style.width = "100px"
        bursucNou.style.height = "100px"
        bursucNou.style.position = "absolute"
        bursucNou.style.backgroundSize = "contain"
        bursucNou.style.backgroundImage = "url(resources/images/badger-1.png)"
        bursucNou.onclick = genoflexiune
        
        let imagBursuci = ["url(resources/images/badger-2.png)","url(resources/images/badger-3.png)","url(resources/images/badger-4.png)","url(resources/images/badger-1.png)"]
        
        let isClicked = false
        function genoflexiune(){
            if (isClicked === true){
                bursucNou.remove()
            }
            else{
                isClicked = true
                for(let i=0;i<4;i++){
                    setTimeout(() => {
                        bursucNou.style.backgroundImage = imagBursuci[i] 
                    }, i*200)
                }

                setTimeout(() => {
                    isClicked = false
                    incGenoflexiuni()
                    genoflexiune()
                }, 1600)
            }
        }

        document.body.append(bursucNou)
    }
    if(e.key === 'p'){
        let sunet = document.createElement('audio')
        sunet.src = "resources/badger.mp3"
        document.body.append(sunet)
        sunet.play()
    }
}



