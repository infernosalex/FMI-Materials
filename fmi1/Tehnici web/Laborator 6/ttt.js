let playerName = prompt("Hai să jucăm X și 0. Cum te cheamă?");
let symbols = ['X', '0'];
let playerSymbol = prompt(`Bună, ${playerName}. Cu ce vrei să joci? X sau 0? X începe primul.`);
let computerSymbol = symbols.find(symbol => symbol !== playerSymbol);

let board = Array(9).fill("?");

function print_board(board) {
    let display = "";
    for (let i = 0; i < 9; i += 3) {
        display += `| ${board[i] === "?" ? i + 1 : board[i]} | ${board[i + 1] === "?" ? i + 2 : board[i + 1]} | ${board[i + 2] === "?" ? i + 3 : board[i + 2]} |\n`;
    }
    return display;
}

function valid(position, board) {
    return position >= 1 && position <= 9 && board[position - 1] === "?";
}

function win(board, symbol) {
    const winningCombinations = [
        [0, 1, 2], [3, 4, 5], [6, 7, 8], // Linii
        [0, 3, 6], [1, 4, 7], [2, 5, 8], // Coloane
        [0, 4, 8], [2, 4, 6]             // Diagonale
    ];
    // Pentru fiecare combinatie verificam daca toate elementele sunt egale cu simbolul
    for (let combination of winningCombinations) {
        if (combination.every(cell => board[cell] === symbol)) {
            return true;
        }
    }
    return false;
}

function draw(board) {
    return board.every(cell => cell !== "?");
}

function computer_move(board) {
    let position;
    do {
        position = Math.floor(Math.random() * 9) + 1;
    } while (!valid(position, board));
    board[position - 1] = computerSymbol;
}

while (true) {
    let position = parseInt(prompt(`${print_board(board)}\nUnde vrei să pui următorul semn, spunand numarul in baza 2?`), 2);

    if (!valid(position, board)) {
        alert("Poziția este invalidă sau deja ocupată. Încearcă din nou.");
        continue;
    }
    board[position - 1] = playerSymbol;

    if (win(board, playerSymbol)) {
        alert(`Bravo, ${playerName}, ai câștigat!`);
        break;
    } else if (draw(board)) {
        alert("Remiză!");
        break;
    }

    computer_move(board);

    if (win(board, computerSymbol)) {
        alert("Ai pierdut :(");
        break;
    } else if (draw(board)) {
        alert("Remiză!");
        break;
    }
}

