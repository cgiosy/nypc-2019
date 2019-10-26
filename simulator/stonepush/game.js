// game.js
// 뇌 비우고 짠거라 코드 상태가 안좋음
'use strict';
let N, M, initialized = false;
let map, win_pos, status;
let status_stack, status_stack2;
let command_stack, command_stack2;

function clone(obj) {
    return JSON.parse(JSON.stringify(obj));
}
function draw() {
    if(!initialized) return;

    let html = '';
    const[start_pos, stone_pos]=status;
    for(let i = 0; i < N; i++) {
        html += '<div class="line">'
            for(let j = 0; j < M; j++) {
            if(!map[i][j]) {
                html += '<div class="wall"></div>';
            } else if(i === start_pos[0] && j === start_pos[1]) {
                html += '<div class="player"></div>';
            } else if(
                i === stone_pos[0] && j === stone_pos[1] ||
                i === stone_pos[0]+1 && j === stone_pos[1] ||
                i === stone_pos[0] && j === stone_pos[1]+1 ||
                i === stone_pos[0]+1 && j === stone_pos[1]+1) {
                html += '<div class="stone"></div>';
            } else if(
                i === win_pos[0] && j === win_pos[1] ||
                i === win_pos[0]+1 && j === win_pos[1] ||
                i === win_pos[0] && j === win_pos[1]+1 ||
                i === win_pos[0]+1 && j === win_pos[1]+1) {
                html += `<div class="win" onclick="go([${i}, ${j}])"></div>`;
            } else {
                html += `<div class="empty" onclick="go([${i}, ${j}])"></div>`;
            }
        }
        html += '</div>';
    }
    document.getElementById('game').innerHTML = html;
    document.getElementById('command').textContent = command_stack.join('');
}
function check_win() {
    const[y, x] = status[1];
    const[u, v] = win_pos;
    if(y === u && x === v) {
        alert('클리어 완료! 복사를 눌러 제출해 주세요.');
    }
}
function init(input) {
    input = input.split(/[\r\n]+/);
    N = Number(input[0].split(' ')[0]);
    M = Number(input[0].split(' ')[1]);
    map = Array.from(Array(N), () => new Array(M));
    input = input.slice(1);
    let start_pos, stone_pos; win_pos = undefined;
    for(let i = 0; i < N; i++) {
        for(let j = 0; j < M; j++) {
            const c = input[i][j];
            if(c === 'X') {
                map[i][j] = 0;
            } else {
                map[i][j] = 1;
                if(c === 'O') {
                    start_pos = [i, j];
                } else if(c === '*' && stone_pos === undefined) {
                    stone_pos = [i, j];
                } else if(c === '-' && win_pos === undefined) {
                    win_pos = [i, j];
                }
            }
        }
    }
    status = [start_pos, stone_pos];
    status_stack = [], status_stack2 = [];
    command_stack = [], command_stack2 = [];
    initialized = true;
    draw();
}
function move(command, drawable = true) {
    if(!initialized) return;

    command_stack2 = [];
    status_stack2 = [];
    const[[i, j], [y, x]] = status;
    status_stack.push(clone(status));
    command_stack.push(clone(command));
    if(command === 'U' && map[i-1][j] && !(i === y+2 && (j === x || j === x+1) && !(map[y-1][x] && map[y-1][x+1]))) {
        status[0][0]--;
        if(i === y+2 && (j === x || j === x+1) && map[y-1][x] && map[y-1][x+1]) {
            status[1][0]--;
        }
    } else if(command === 'D' && map[i+1][j] && !(i === y-1 && (j === x || j === x+1) && !(map[y+2][x] && map[y+2][x+1]))) {
        status[0][0]++;
        if(i === y-1 && (j === x || j === x+1) && map[y+2][x] && map[y+2][x+1]) {
            status[1][0]++;
        }
    } else if(command === 'L' && map[i][j-1] && !((i === y || i === y+1) && j === x+2 && !(map[y][x-1] && map[y+1][x-1]))) {
        status[0][1]--;
        if((i === y || i === y+1) && j === x+2 && map[y][x-1] && map[y+1][x-1]) {
            status[1][1]--;
        }
    } else if(command === 'R' && map[i][j+1] && !((i === y || i === y+1) && j === x-1 && !(map[y][x+2] && map[y+1][x+2]))) {
        status[0][1]++;
        if((i === y || i === y+1) && j === x-1 && map[y][x+2] && map[y+1][x+2]) {
            status[1][1]++;
        }
    } else {
        status_stack.pop();
        command_stack.pop();
        return;
    }
    if(drawable) {
        draw();
    }
    check_win();
}
function undo() {
    if(!initialized) return;

    if(command_stack.length && status_stack.length) {
        command_stack2.push(command_stack.pop());
        status_stack2.push(status = status_stack.pop());
        draw();
    }
}
function redo() {
    if(!initialized) return;

    if(command_stack2.length && status_stack2.length) {
        command_stack.push(command_stack2.pop());
        status_stack.push(status = status_stack2.pop());
        draw();
    }
}
function go(pos) {
    const dy = [-1, 1, 0, 0], dx = [0, 0, -1, 1];
    const ds = ['D', 'U', 'R', 'L'];
    const[[a, b], [u, v]] = status;
    let prev = Array.from(Array(N), () => Array(M));
    let queue = [pos];
    prev[pos[0]][pos[1]] = ['X', -1, -1];
    while(queue.length) {
        const[i, j] = queue.shift();
        if(i === a && j === b) {
            let y = i, x = j;
            while(prev[y][x][0] !== 'X') {
                const n = y;
                move(prev[y][x][0], false);
                y = prev[y][x][1];
                x = prev[n][x][2];
            }
            draw();
            return;
        }
        for(let di = 0; di < 4; di++) {
            const y = i + dy[di], x = j + dx[di];
            if(map[y][x] && prev[y][x] === undefined && (y - u < 0 || 1 < y - u || x - v < 0 || 1 < x - v)) {
                queue.push([y, x]);
                prev[y][x] = [ds[di], i, j];
            }
        }
    }
}

setTimeout(function(){
    document.body.addEventListener('keydown', function(e) {
        if (event.defaultPrevented) {
            return;
        }
        switch (event.key) {
            case 'Up':
            case 'ArrowUp':
                move('U');
            break;
            case 'Down':
            case 'ArrowDown':
                move('D');
            break;
            case 'Left':
            case 'ArrowLeft':
                move('L');
            break;
            case 'Right':
            case 'ArrowRight':
                move('R');
            break;
            case 'z':
            case 'Z':
                undo();
            break;
            case 'x':
            case 'X':
                redo();
            break;
            case 'r':
            case 'R':
                const input = document.getElementById('input').value;
                init(input);
            break;
            default:
            return;
        }
        event.preventDefault();
    });

    document.getElementById('init').onclick = function(e) {
        const input = document.getElementById('input').value;
        init(input);
    };

    document.getElementById('copy').onclick = function(e) {
        document.getElementById('command').select();
        document.execCommand('copy');
        alert('복사 완료!');
    };
}, 500);