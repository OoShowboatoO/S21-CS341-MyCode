#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

struct Token {
    int x, y;
    Token(int t_x = 0, int t_y = 0): x(t_x), y(t_y) {}
};

struct Vertex
{
    int A_x, A_y, B_x, B_y, step;
    vector<string> path;
    Vertex(int a_x = 0, int a_y = 0, int b_x = 0, int b_y = 0, int Step = 0): 
    A_x(a_x), A_y(a_y), B_x(b_x), B_y(b_y), step(Step) {}
};


void BFS(Token player_A, Token player_B, vector<Token> Obstacles, Token target, int grid_size) {
    
    int visited[grid_size][grid_size][grid_size][grid_size] {0};
    Vertex start(player_A.x, player_A.y, player_B.x, player_B.y);
    Vertex curr;
    queue<Vertex> que;
    que.push(start);
    visited[player_A.x][player_A.y][player_B.x][player_B.y] = 1;

    while(que.size()) {

        curr = que.front();
        que.pop();
        if ((curr.A_x == target.x && curr.A_y == target.y) || (curr.B_x == target.x && curr.B_y == target.y)) { // h
            cout << curr.step << endl;
            for (auto& move : curr.path) {
                cout << move << endl;
            }
            return;
        }

        Token new_A(curr.A_x, curr.A_y);
        Token new_B(curr.B_x, curr.B_y);
        
        vector<Token> A_Obstacles = Obstacles; // The map that Player A uesd
        A_Obstacles.push_back(new_B);
    
        vector<Token> B_Obstacles = Obstacles; // The map that Player B uesd
        B_Obstacles.push_back(new_A);
    

        for (int i = 0; i < 8; i ++) {
            int new_A_x = curr.A_x;
            int new_A_y = curr.A_y;
            int new_B_x = curr.B_x;
            int new_B_y = curr.B_y;
            bool found_obstacle = false;
            string new_move;
            
            if (i == 0) {   //  A moves up
                new_A_y = 0;
                for (auto& obstacle : A_Obstacles) {
                    if (obstacle.x == curr.A_x && obstacle.y < curr.A_y) { 
                        found_obstacle = true;
                        if (new_A_y <= obstacle.y) {
                            new_A_y = obstacle.y;
                        }
                    } 
                }
                if(found_obstacle) {
                    new_A_y += 1;
                } 
                new_move = "A up";

            } else if (i == 1) {    // A moves down
                new_A_y = grid_size - 1;
                for (auto& obstacle : A_Obstacles) {  
                    if (obstacle.x == curr.A_x && obstacle.y > curr.A_y) { 
                        found_obstacle = true;
                        if (new_A_y >= obstacle.y) {  // more than 1 obstacles on the move
                            new_A_y = obstacle.y;
                        }
                    }
                }
                if (found_obstacle) {
                    new_A_y -= 1;
                }
                new_move = "A down";

            } else if (i == 2) {    // A moves right
                new_A_x = grid_size - 1;
                for (auto& obstacle : A_Obstacles) {
                    if (obstacle.y == curr.A_y && obstacle.x > curr.A_x) { 
                        found_obstacle = true;
                        if (new_A_x >= obstacle.x) {  // more than 1 obstacles on the move
                            new_A_x = obstacle.x;
                        }
                    }
                }
                if (found_obstacle) {
                    new_A_x -= 1;
                }
                new_move = "A right";

            } else if (i == 3) {    // A moves left
                new_A_x = 0;
                for (auto& obstacle : A_Obstacles) {
                    if (obstacle.y == curr.A_y && obstacle.x < curr.A_x) { 
                        found_obstacle = true;
                        if (new_A_x <= obstacle.x) {  // more than 1 obstacles on the move
                            new_A_x = obstacle.x;
                        }
                    }
                }
                if (found_obstacle) {
                    new_A_x += 1;
                }
                new_move = "A left";


            } else if (i == 4) {    // B moves up
                new_B_y = 0;
                for (auto& obstacle : B_Obstacles) {
                    if (obstacle.x == curr.B_x && obstacle.y < curr.B_y) { 
                        found_obstacle = true;
                        if (new_B_y <= obstacle.y) {
                            new_B_y = obstacle.y;
                        }
                    } 
                }
                if(found_obstacle) {
                    new_B_y += 1;
                }
                new_move = "B up";

            } else if (i == 5) {    // B moves down
                new_B_y = grid_size - 1;
                for (auto& obstacle : B_Obstacles) {
                    if (obstacle.x == curr.B_x && obstacle.y > curr.B_y) { 
                        found_obstacle = true;
                        if (new_B_y >= obstacle.y) {  // more than 1 obstacles on the move
                            new_B_y = obstacle.y;
                        } 
                    }
                }
                if (found_obstacle) {
                    new_B_y -= 1;
                }
                new_move = "B down";

            } else if (i == 6) {    // B moves right
                new_B_x = grid_size - 1;
                for (auto& obstacle : B_Obstacles) {
                    if (obstacle.y == curr.B_y && obstacle.x > curr.B_x) { 
                        found_obstacle = true;
                        if (new_B_x >= obstacle.x) {  // more than 1 obstacles on the move
                            new_B_x = obstacle.x;
                        }
                    }
                }
                if (found_obstacle) {
                    new_B_x -= 1;
                }
                new_move = "B right";

            } else{ // B moves left
                new_B_x = 0;
                for (auto& obstacle : B_Obstacles) {
                    if (obstacle.y == curr.B_y && obstacle.x < curr.B_x) { 
                        found_obstacle = true;
                        if (new_B_x <= obstacle.x) {  // more than 1 obstacles on the move
                            new_B_x = obstacle.x;
                        }
                    }
                }
                if (found_obstacle) {
                    new_B_x += 1;
                }
                new_move = "B left";
            }

            if (visited[new_A_x][new_A_y][new_B_x][new_B_y] == 0) {
                Vertex new_vertex(new_A_x, new_A_y, new_B_x, new_B_y, curr.step + 1);
                new_vertex.path = curr.path;
                new_vertex.path.push_back(new_move);
                que.push(new_vertex);
                visited[new_A_x][new_A_y][new_B_x][new_B_y] = 1;
            }
        }
    }
    cout << "-1" << endl;
}


int main() {
    int grid_size;
    string row;
    string line;
    getline(cin, row);
    stringstream ss(row);
    ss >> grid_size;
    
    Token player_A;
    Token player_B;
    vector<Token> Obstacles;
    Token target;

    for (int i = 0; i < grid_size; i++) {
        getline(cin, row);
        stringstream sss(row);
        sss >> line;
        
        for (int j = 0; j < grid_size; j++) {
            char content = line[j];
            if (content == 'A') {
                player_A.x = j;
                player_A.y = i;

            } else if(content == 'B') {
                player_B.x = j;
                player_B.y = i;

            } else if(content == 'T') {
                target.x = j;
                target.y = i;

            } else if(content == '#') {
                Token obstacle(j, i);
                Obstacles.push_back(obstacle);
            }
        }
    }

    BFS(player_A, player_B, Obstacles, target, grid_size);

    return 0;
}
