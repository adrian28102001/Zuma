#include "usefulHeaders.h"


int main() {
    srand(time(NULL));
    RenderWindow window(VideoMode(1900, 1000), "ZUMA 2020");
    window.setFramerateLimit(60);

    Image icon;
    icon.loadFromFile("frog.png");

    bool won = false;

    //Backgorund
    Texture textBackground;
    textBackground.loadFromFile("background.jfif");
    Sprite Background;
    Vector2u size = textBackground.getSize();
    Background.setTexture(textBackground);
    Background.setOrigin(size.x / 2.f, size.y / 2.f);

    //Score
    int intScore = 0;
    Text Score;
    Score.setPosition(10, 10);
    Score.setCharacterSize(30);

    Font arial;
    arial.loadFromFile("ARCADECLASSIC.TTF");
    Score.setFont(arial);

    ostringstream stringScore;
    stringScore << "Score " << intScore;
    Score.setString(stringScore.str());

    //Win screen
    Text you_win;
    you_win.setPosition(window.getSize().x / 2.f - 500, window.getSize().y / 2.f);
    you_win.setCharacterSize(60);
    you_win.setFont(arial);
    you_win.setFillColor(Color::Green);
    ostringstream win;
    win << "YOU SAVED THE WORLD FROM A PANDEMIC!";
    you_win.setString(win.str());

    //Lose screen
    Text Lose;
    Lose.setPosition(window.getSize().x / 2.f - 500, window.getSize().y / 2.f);
    Lose.setCharacterSize(60);
    Lose.setFont(arial);
    Lose.setFillColor(Color::Red);
    ostringstream loss;
    loss << "STAY SAFE AND GET IN QUARANTINE!";
    Lose.setString(loss.str());

    //Lives
    int intLives = 3;
    Text lives;
    lives.setPosition(10, 50);
    lives.setCharacterSize(30);
    lives.setFont(arial);
    lives.setFillColor(Color::Green);
    ostringstream stringLives;
    stringLives << "Lives " << intLives;
    lives.setString(stringLives.str());

    //Frog
    Texture FrogTexture;
    FrogTexture.loadFromFile("frog.png");
    Sprite Frog;
    Frog.setTexture(FrogTexture);
    Vector2f FrogPostition(window.getSize().x - Frog.getGlobalBounds().width, 0.f);
    Frog.setPosition(FrogPostition);

    //finishline
    Texture FinishLineTexture;
    FinishLineTexture.loadFromFile("finishline.png");
    Sprite finish;
    finish.setTexture(FinishLineTexture);
    finish.setPosition(window.getSize().x - finish.getGlobalBounds().width, window.getSize().y -300);

    //Balls
    CircleShape projectile;
    projectile.setFillColor(Color::White);
    projectile.setRadius(5.f); // leave

    // BLock to display the enemy
    Texture enemyTextureRed;
    enemyTextureRed.loadFromFile("red.png");
    Sprite enemyRed;
    enemyRed.setTexture(enemyTextureRed);
    enemyRed.setScale(Vector2f(0.2f, 0.2f));

    //BlockOfYellow
    Texture enemyTextureYellow;
    enemyTextureYellow.loadFromFile("yellow.png");
    Sprite enemyYellow;
    enemyYellow.setTexture(enemyTextureYellow);
    enemyYellow.setScale(Vector2f(0.2f, 0.2f));

    //BlockOfGreen
    Texture enemyTextureGreen;
    enemyTextureGreen.loadFromFile("green.png");
    Sprite enemyGreen;
    enemyGreen.setTexture(enemyTextureGreen);
    enemyGreen.setScale(Vector2f(0.2f, 0.2f));

    Texture playerTexture;
    playerTexture.loadFromFile("syringe.png");
    Sprite player;
    player.setTexture(playerTexture);
    player.setScale(Vector2f(0.3f, 0.3f));

    player.setPosition(window.getSize().x / 2.f, window.getSize().y - 200.f);
    Vector2f playerCenter;
    int shootTimer = 0;

    vector<CircleShape> projectiles;
    projectiles.push_back(CircleShape(projectile));

    vector<Sprite> enemies;

    int enemySpawnTimer = 0;
    float movementspeed = 1.f;
    int speedSpawning = 80;
    int shootingTime = 30;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape){
                window.close();
            }

        }

        //If lives is 0
        if (intLives <= 0) {
            Frog.setPosition(window.getSize().x/2.f - 200, window.getSize().y/2.f - Frog.getGlobalBounds().height);
            window.clear();
            window.draw(Background);
            window.draw(Frog);
            window.draw(Lose);
            window.draw(lives);
            window.display();
        }

            //Game loop
        else if (!won) {
            //Update
            //Player
            playerCenter = Vector2f(player.getPosition().x, player.getPosition().y);
            player.setPosition(Mouse::getPosition(window).x, player.getPosition().y);

            //Blocks out the boarders
            if (player.getPosition().x >= window.getSize().x * 0.75)
                player.setPosition(window.getSize().x * 0.75, player.getPosition().y);
            if (player.getPosition().x <= 0)
                player.setPosition(0, player.getPosition().y);

            //Projectiles
            if (shootTimer < shootingTime)
                shootTimer++;
            if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= shootingTime) // shoot
            {
                projectile.setPosition(playerCenter);
                projectiles.push_back(CircleShape(projectile));
                shootTimer = 0;
            }
            for (size_t i = 0; i < projectiles.size(); i++) {
                projectiles[i].move(0.f, -10.f);
                if (projectiles[i].getPosition().y <= 0)
                    projectiles.erase(projectiles.begin() + i);
            }

            //Enemies
            if (enemySpawnTimer < speedSpawning)
                enemySpawnTimer++;
            //Spawn enemies
            if (enemySpawnTimer >= speedSpawning) {
                enemyRed.setPosition((rand() % int(window.getSize().x - enemyRed.getGlobalBounds().width)) * 0.75, 0.f);
                if (intScore > 500) {
                    enemyRed.setScale(Vector2f(0.25f, 0.25f));
                    enemies.push_back(Sprite(enemyRed));//more shots to kill red
                    enemies.push_back(Sprite(enemyRed));
                } else {
                    enemies.push_back(Sprite(enemyRed));
                }

                reset:
                enemyYellow.setPosition((rand() % int(window.getSize().x - enemyYellow.getGlobalBounds().width)) * 0.75, 0.f);
                enemyGreen.setPosition((rand() % int(window.getSize().x - enemyGreen.getGlobalBounds().width)) * 0.75, 0.f);

                //handler for intersection of red and yellow balls
                if (enemyRed.getGlobalBounds().intersects(enemyYellow.getGlobalBounds()) ||
                    enemyRed.getGlobalBounds().intersects(enemyGreen.getGlobalBounds()) ||
                    enemyYellow.getGlobalBounds().intersects(enemyGreen.getGlobalBounds())) {
                    goto reset;
                }
                enemies.push_back(Sprite(enemyYellow));
                enemies.push_back(Sprite(enemyGreen));
                enemySpawnTimer = 0;
            }

            //Enemy hits boundary Lives counter
            for (size_t i = 0; i < enemies.size(); i++) {
                enemies[i].move(0.f, movementspeed);

                if (enemies[i].getPosition().y >= window.getSize().y - enemies[i].getGlobalBounds().height) {
                    enemies.erase(enemies.begin() + i);
                    intLives--;
                    stringLives.str("");
                    stringLives << "Lives " << intLives;
                    lives.setString(stringLives.str());
                }
            }
            if (intLives == 2)
                lives.setFillColor(Color::Yellow);
            if (intLives == 1)
                lives.setFillColor(Color::Red);
            if (intLives == 0) {
                lives.setFillColor(Color::Red);
            }
            //Collision
            for (size_t i = 0; i < projectiles.size(); i++) {
                for (size_t j = 0; j < enemies.size(); j++) {
                    if (projectiles[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
                        projectiles.erase(projectiles.begin() + i);
                        enemies.erase(enemies.begin() + j);
                        intScore++;
                        stringScore.str("");
                        stringScore << "Score " << intScore;
                        Score.setString(stringScore.str());
                        break;
                    }
                }
            }

            //Slow
            if (intScore >= 50 && intScore < 100) {
                shootingTime = 18;
                speedSpawning = 60;
                movementspeed = 1.3f;
                Score.setFillColor(Color::Green);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 50.f);
            }
            //Average
            if (intScore >= 100 && intScore < 200) {
                shootingTime = 14;
                speedSpawning = 50;
                movementspeed = 1.6f;
                Score.setFillColor(Color::Green);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 100.f);
            }
            //Medium
            if (intScore >= 200 && intScore < 300) {
                shootingTime = 12;
                speedSpawning = 45;
                movementspeed = 1.8f;
                Score.setFillColor(Color::Yellow);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 150.f);
            }
            //Intermediate
            if (intScore >= 300 && intScore < 400) {
                shootingTime = 10;
                speedSpawning = 39;
                movementspeed = 2.0f;
                Score.setFillColor(Color::Yellow);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 200.f);
            }
            //Fast
            if (intScore >= 400 && intScore <500) {
                shootingTime = 9;
                speedSpawning = 38;
                movementspeed = 2.4f;
                Score.setFillColor(Color::Magenta);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 250.f);
            }

            //Next level with Big enemies
            if (intScore >= 500 && intScore < 600) {
                shootingTime = 8;
                speedSpawning = 37;
                movementspeed = 2.5f;
                Score.setFillColor(Color::Magenta);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 300.f);
            }
            if (intScore >= 600 && intScore < 700) {
                shootingTime = 7;
                speedSpawning = 36;
                movementspeed = 2.7f;
                Score.setFillColor(Color::Red);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 400.f);
            }
            if (intScore >= 700) {
                shootingTime = 7;
                speedSpawning = 33;
                movementspeed = 2.9f;
                Score.setFillColor(Color::Red);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 500.f);
            }

            if ((Frog.getPosition().y == (500.f)) && intScore==1000) {
                won = true;
            }

            //Draw
            window.clear();
            window.draw(Background);
            window.draw(Frog);
            window.draw(finish);
            window.draw(player);
            window.draw(Score);
            window.draw(lives);

            for (size_t i = 0; i < enemies.size(); i++) {
                window.draw(enemies[i]);
            }
            for (size_t i = 0; i < projectiles.size(); i++) {
                window.draw(projectiles[i]);
            }
            window.display();
        }

            //Winning screen
        else {
            window.clear();
            window.draw(Background);
            window.draw(Frog);
            window.draw(finish);
            window.draw(you_win);
            window.display();
        }
    }
    return 0;
}