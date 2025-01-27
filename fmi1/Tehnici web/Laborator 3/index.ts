let header = document.querySelector('header');
if (header == null) {
		throw new Error('Header not found');
}

window.addEventListener('scroll' , function () {
    let window_top = this.scrollY;
    if (window_top == 0) {
        header.classList.remove('resize');
    }else {
        header.classList.add('resize');
    }
});

let topSpace = document.querySelector('#top-space') as HTMLElement;
if (topSpace == null) {
		throw new Error('Top space not found');
}
let headerHeight = header.clientHeight;
topSpace.style.height = headerHeight + 'px';