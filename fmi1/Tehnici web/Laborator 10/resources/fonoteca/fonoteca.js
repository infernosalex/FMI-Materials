window.onload = function() {
   fetch('albums.json')
       .then(response => response.json())
       .then(albums => {
           // console.log('Albums:', albums);
           const gallery = document.getElementById('gallery');
           
           gallery.style.display = 'grid';
           gallery.style.gridTemplateColumns = 'repeat(3, 1fr)';
           gallery.style.gap = '20px';
           
           albums.forEach((album, index) => {
               const albumDiv = document.createElement('div');
               albumDiv.className = 'album';
               // console.log(album);
               
               const albumTitle = document.createElement('h2');
               albumTitle.textContent = album.name;
               albumDiv.appendChild(albumTitle);

               const albumCover = document.createElement('img');
               albumCover.src = '/images/'+album.image;
               albumCover.class = 'albumCover';
               albumCover.id = index;
               
               albumCover.addEventListener('click', function() {
                   // console.log('clicked');
                  console.log(albumCover.id);
                  var promiseFetch = fetch('albums/'+albumCover.id+'.json');

                  
                  promiseFetch.then((response) => {
                     if (!response.ok) {
                        throw new Error(`HTTP error: ${response.status}`);
                     }
                        return response.text();
                     }).then(function(text) {    
                        // Aici vine codul util
                        // console.log(text);
                        
                        const infoDiv = document.getElementById('info');
                        infoDiv.innerHTML = '';
                        const albumInfo = JSON.parse(text);
                        // console.log(albumInfo);

                        const albumTitle = document.createElement('h2');
                        albumTitle.textContent = albumInfo.name;
                        infoDiv.appendChild(albumTitle);

                        const albumCover = document.createElement('img');
                        albumCover.src = '/images/'+albumInfo.image;
                        albumCover.class = 'albumCover';
                        infoDiv.appendChild(albumCover);

                        const albumYear = document.createElement('h5');
                        albumYear.textContent = albumInfo.year;
                        infoDiv.appendChild(albumYear);

                        
                     }).catch(function(err){
                        alert(err);}); 
                     });

               const artist = document.createElement('p'); 
               artist.textContent = album.artist;

               albumDiv.appendChild(albumCover);
               albumDiv.appendChild(artist);
               
               gallery.appendChild(albumDiv);
           });
       })
       .catch(error => console.error('Error loading albums:', error));
};