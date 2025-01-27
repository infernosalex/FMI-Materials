window.onload = function() {
    let counter = document.createElement('div');
    counter.id = 'counter';
    counter.style.position = 'fixed';
    counter.style.top = '50px';
    counter.style.left = '10px';
    document.body.appendChild(counter);

    let range = document.createElement('input');
    range.type = 'range';
    range.id = 'size';
    range.min = '20';
    range.max = '150';
    range.value = '20';
    document.body.appendChild(range);

    document.addEventListener('keydown', keyDownListener);

    if (!localStorage.getItem('dotCount')) {
        localStorage.setItem('dotCount', '0');
    }
    updateCounter();
}

function keyDownListener(event) {
    const colors = {
        'r': 'red',
        'g': 'green',
        'y': 'yellow',
        'b': 'blue'
    };

    if (colors[event.key]) {
        createDot(colors[event.key]);
    }
}

function createDot(color) {
    const dot = document.createElement('div');
    const size = document.getElementById('size').value;
    
    dot.style.width = size + 'px';
    dot.style.height = size + 'px';
    dot.style.backgroundColor = color;
    dot.style.borderRadius = '50%';
    dot.style.position = 'absolute';
    dot.style.left = Math.random() * (window.innerWidth - size) + 'px';
    dot.style.top = Math.random() * (window.innerHeight - size) + 'px';
    
    dot.addEventListener('click', () => createDotSameSize(color,size));
    
    document.body.appendChild(dot);
    
    let count = parseInt(localStorage.getItem('dotCount')) + 1;
    localStorage.setItem('dotCount', count.toString());
    updateCounter();
}

function createDotSameSize(color, size){
    const dot = document.createElement('div');
    dot.style.width = size + 'px';
    dot.style.height = size + 'px';
    dot.style.backgroundColor = color;
    dot.style.borderRadius = '50%';
    dot.style.position = 'absolute';
    dot.style.left = Math.random() * (window.innerWidth - size) + 'px';
    dot.style.top = Math.random() * (window.innerHeight - size) + 'px';
    
    dot.addEventListener('click', () => createDotSameSize(color,size));
    
    document.body.appendChild(dot);
    
    let count = parseInt(localStorage.getItem('dotCount')) + 1;
    localStorage.setItem('dotCount', count.toString());
    updateCounter();
}

function updateCounter() {
    const counter = document.getElementById('counter');
    counter.textContent = `dotzzz: ${localStorage.getItem('dotCount')}`;
}