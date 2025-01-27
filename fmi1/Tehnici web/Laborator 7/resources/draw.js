function drawTable(nrows, ncols) {
/* 
   1. Generați un tabel cu 'nrows' rânduri și 'ncols' coloane 
   și adăugați-l în div-ul cu id-ul 'container'. 
*/
   var container = document.getElementById("container");
   var table = document.createElement("table");
   var tbody = document.createElement("tbody");

   for (let i = 0; i < nrows; i++) {
      var row = document.createElement("tr");
      for (let j = 0; j < ncols; j++) {
         var cell = document.createElement("td");
         cell.classList.add(`r${i}`,`c${j}`);
         row.appendChild(cell);
      }
      tbody.appendChild(row);
   }
   table.appendChild(tbody);
   container.appendChild(table);

}

function colorCol(column, color) {
/*
   2. Colorați coloana 'column' din tabla de desenat cu culoarea 'color'.
*/
   var cells = document.getElementsByClassName(`c${column}`);
   for (let cell of cells) {
      cell.style.backgroundColor = color;
   }

}

function colorRow(row, color) {
/*
   2. Colorați rândul 'row' din tabla de desenat cu culoarea 'color'.
*/
   var cells = document.getElementsByClassName(`r${row}`);
   for (let cell of cells) {
      cell.style.backgroundColor = color;
   }
}

function rainbow(target) {
   let colors = ["rgb(255, 0, 0)", "rgb(255, 154, 0)", "rgb(240, 240, 0)", "rgb(79, 220, 74)", "rgb(63, 218, 216)", "rgb(47, 201, 226)", "rgb(28, 127, 238)", "rgb(95, 21, 242)", "rgb(186, 12, 248)", "rgb(251, 7, 217)"];
/*
   3. Desenați un curcubeu pe verticală sau orizontală conform argumentului 'target' folosind culorile din 'colors' și funcțiile 'colorCol' și 'colorRow'.     
*/
   var table = document.getElementsByTagName("table")[0];
   var rows = table.getElementsByTagName("tr");
   var cols = rows[0].getElementsByTagName("td");

   if (target === "vertical") {
      for (let i = 0; i < cols.length; i++) {
         colorCol(i, colors[i%colors.length]);
      }
   } else if (target === "horizontal") {
      for (let i = 0; i < rows.length; i++) {
         colorRow(i, colors[i%colors.length]);
      }
   }
}

function getNthChild(element, n) {
/*
   4. Întoarceți al n-lea element copil al unui element dat ca argument.
*/
   return element.children[n];
};

function drawPixel(row, col, color) {	
/*
   5. Colorați celula de la linia 'row' și coloana 'col' cu culoarea `color'.
*/
   var cell = document.querySelector(`.r${row}.c${col}`);
   cell.style.backgroundColor = color;
}

function drawLine(r1, c1, r2, c2, color) {
/*
   6. Desenați o linie (orizontală sau verticală) de la celula aflată 
   pe linia 'r1', coloana 'c1' la celula de pe linia 'r2', coloana 'c2'
   folosind culoarea 'color'. 
   Hint: verificați mai întâi că punctele (r1, c1) și (r2, c2) definesc
   într-adevăr o linie paralelă cu una dintre axe.
*/

   var table = document.getElementsByTagName("table")[0];
   var rows = table.getElementsByTagName("tr");
   var cols = rows[0].getElementsByTagName("td");
   var cells = table.getElementsByTagName("td");

   if (r1 === r2) {
      for (let i = c1; i <= c2; i++) {
         drawPixel(r1, i, color);
      }
   }

   if (c1 === c2) {
      for (let i = r1; i <= r2; i++) {
         drawPixel(i, c1, color);
      }
   }

   // Pt linii oblice derivata intai

}

function drawRect(r1, c1, r2, c2, color) {
/*
   7. Desenați, folosind culoarea 'color', un dreptunghi cu colțul din 
   stânga sus în celula de pe linia 'r1', coloana 'c1', și cu 
   colțul din dreapta jos în celula de pe linia 'r2', coloana 'c2'.
*/
   drawLine(r1, c1, r2, c1, color);
   drawLine(r2, c1, r2, c2, color);
   drawLine(r1, c2, r2, c2, color);
   drawLine(r1, c1, r1, c2, color);

}

function drawPixelExt(row, col, color) {
/*
   8. Colorați celula de la linia 'row' și coloana 'col' cu culoarea 'color'.
   Dacă celula nu există, extindeți tabla de desenat în mod corespunzător.
*/
   var table = document.getElementsByTagName("table")[0];
   var rows = table.getElementsByTagName("tr");
   var cols = rows[0].getElementsByTagName("td");
   var cells = table.getElementsByTagName("td");

   while (row >= rows.length) {
      var newRow = document.createElement("tr");
      for (let i = 0; i < cols.length; i++) {
         var cell = document.createElement("td");
         cell.classList.add(`r${rows.length + 1 }`,`c${i}`);
         newRow.appendChild(cell);
      }
      table.appendChild(newRow);
      rows = table.getElementsByTagName("tr");
   }

   while (col >= cols.length) {
      for (let i = 0; i < rows.length; i++) {
         var cell = document.createElement("td");
         cell.classList.add(`r${i}`,`c${cols.length + 1}`);
         rows[i].appendChild(cell);
      }
      
      cols = rows[0].getElementsByTagName("td");

   }


   drawPixel(row, col, color);
}

function colorMixer(colorA, colorB, amount){
   let cA = colorA * (1 - amount);
   let cB = colorB * (amount);
   return parseInt(cA + cB);
}

function drawPixelAmount(row, col, color, amount) {
   /* 
   9. Colorați celula la linia 'row' și coloana 'col' cu culoarea 'color'
   în funcție de ponderea 'amount' primită ca argument (valoare între 0 și 1). 
   Dacă 'amount' are valoarea:
   1, atunci celula va fi colorată cu 'color'
   0, atunci celula își va păstra culoarea inițială
   pentru orice altă valoare, culoarea inițială și cea dată de argumentul 
   'color' vor fi amestecate. De exemplu, dacă ponderea este 0.5, atunci 
   culoarea inițială și cea nouă vor fi amestecate în proporții egale (50%). 
   */

   /*   
   Hint 1: folosiți funcția colorMixer de mai sus.

   Hint 2: pentru un argument 'color' de forma 'rgb(x,y,z)' puteți folosi
   let newColorArray = color.match(/\d+/g); 
   pentru a obține un Array cu trei elemente, corespunzătoare valorilor
   asociate celor trei culori - newColorArray = [x, y, z]
   
   Hint 3: pentru a afla culoarea de fundal a unui element puteți folosi
   metoda getComputedStyle(element). Accesând proprietatea backgroundColor 
   a obiectului întors, veți obține un string de forma 'rgb(x,y,z)'.
   */

   if(amount === 1) {
      drawPixel(row, col, color);
   }

   if(amount === 0) {
      return;
   }

   let cell = document.querySelector(`.r${row}.c${col}`);
   let currentColor = getComputedStyle(cell).backgroundColor;
   let newColorArray = color.match(/\d+/g);
   let currentColorArray = currentColor.match(/\d+/g);

   let newColor = `rgb(${colorMixer(currentColorArray[0], newColorArray[0], amount)}, ${colorMixer(currentColorArray[1], newColorArray[1], amount)}, ${colorMixer(currentColorArray[2], newColorArray[2], amount)})`;
   drawPixel(row, col, newColor);
}

function delRow(row) {
/*
   10. Ștergeți linia cu numărul 'row' din tabla de desenat.
*/
   var table = document.getElementsByTagName("table")[0];
   var tbody = table.getElementsByTagName("tbody")[0];
   var rows = table.getElementsByTagName("tr");
   var cols = rows[0].getElementsByTagName("td");
   var cells = table.getElementsByTagName("td");

   if (row >= rows.length) {
      return;
   }
   tbody.removeChild(rows[row]);
}

function delCol(col) {
/*
   10. Ștergeți coloana cu numărul 'col' din tabla de desenat.
*/

   var table = document.getElementsByTagName("table")[0];
   var tbody = table.getElementsByTagName("tbody")[0];
   var rows = table.getElementsByTagName("tr");
   var cols = rows[0].getElementsByTagName("td");
   var cells = table.getElementsByTagName("td");

   if (col >= cols.length) {
      return;
   }

   for (let i = 0; i < rows.length; i++) {
      var cell = getNthChild(rows[i], col);
      rows[i].removeChild(cell);
   }



}

function shiftRow(row, pos) {
/*
   11. Aplicați o permutare circulară la dreapta cu 'pos' poziții a
   elementelor de pe linia cu numărul 'row' din tabla de desenat. 
*/
}

function jumble() {
/*
   12. Folosiți funcția 'shiftRow' pentru a aplica o permutare circulară
   cu un număr aleator de poziții fiecărei linii din tabla de desenat.
*/
}

function transpose() {
/*
   13. Transformați tabla de desenat în transpusa ei.
*/
}

function flip(element) {
/*
   14. Inversați ordinea copiilor obiectului DOM 'element' primit ca argument.
*/
}

function mirror() {
/*
   15. Oglindiți pe orizontală tabla de desenat: luați jumătatea stângă a tablei, 
   aplicați-i o transformare flip și copiați-o în partea dreaptă a tablei.
*/
}

function smear(row, col, amount) {
/*
   16. Întindeți culoarea unei celule de pe linia 'row' și coloana 'col' în celulele
   învecinate la dreapta, conform ponderii date de 'amount' (valoare între 0 și 1).
   Cu colorarea fiecărei celule la dreapta, valoarea ponderii se înjumătățește. 
   Hint: folosiți funcția 'drawPixelAmount'.
*/
}


window.onload = function(){
    const rows = 15  ;
    const cols = 15;	
    /* 
    drawTable(rows, cols);
    ... 
    */
   drawTable(rows, cols);
   rainbow("horizontal");
   //drawPixel(1, 1, "red");
   //drawLine(1, 1, 1, 5, "blue");
   drawRect(2, 2, 8, 4, "black");
   drawPixelExt(20, 20, "green");
   drawPixelAmount(1, 1, "rgb(0, 0, 0)", 0.5);
   delRow(1);
   delCol(1);
}


