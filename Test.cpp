#include "doctest.h"
#include "sources/Team.hpp"
#include <math.h>

using namespace ariel;

TEST_CASE("1. 1v1 ninja win"){
    YoungNinja* ninja = new YoungNinja("nin-ja", Point(20, 20));
    Cowboy* cowboy = new Cowboy("cow-boy", Point(20, 20));

    while(ninja->isAlive() && cowboy->isAlive()){
        ninja->slash(cowboy);
        cowboy->shoot(ninja);
    }

    CHECK(ninja->isAlive() == true);
    CHECK(cowboy->isAlive() == false);

    delete ninja;
    delete cowboy;
}

TEST_CASE("2. 1v1 cowboy win"){
    YoungNinja* ninja = new YoungNinja("nin-ja", Point(400, 400));
    Cowboy* cowboy = new Cowboy("cow-boy", Point(20, 20));

    while(ninja->isAlive() && cowboy->isAlive()){
        ninja->slash(cowboy);
        cowboy->shoot(ninja);
    }

    CHECK(ninja->isAlive() == false);
    CHECK(cowboy->isAlive() == true);

    delete ninja;
    delete cowboy;
}

TEST_CASE("3. point moving correct distance"){
    Point start(10,10);
    Point end(20,20);
    Point middle = Point::moveTowards(start, end, sqrt(5 * 5 + 5 * 5));

    CHECK(middle == Point(15, 15));

    Point start2(0, 0);
    Point end2(10, 0);
    Point middle2 = Point::moveTowards(start2, end2, 7.5);

    CHECK(middle2 == Point(7.5, 0));
}

TEST_CASE("4. 1v1 ninja movement"){
    YoungNinja* ninja = new YoungNinja("nin-ja", Point(0, 0));
    Cowboy* cowboy = new Cowboy("cow-boy", Point(0, 50));

    while(ninja->isAlive() && cowboy->isAlive()){
        ninja->slash(cowboy);
    }

    CHECK(ninja->getLocation() == Point(0, 50));
    CHECK(ninja->isAlive() == true);
    CHECK(cowboy->isAlive() == false);

    delete ninja;
    delete cowboy;
}

TEST_CASE("5. 3v1 correct hp subtraction"){
    Ninja* ninja = new TrainedNinja("nin-ja", Point(0, 0));
    Cowboy* cowboy1 = new Cowboy("cow-boy1", Point(0, 50));
    Cowboy* cowboy2 = new Cowboy("cow-boy2", Point(0, 50));
    Cowboy* cowboy3 = new Cowboy("cow-boy3", Point(0, 50));

    //120 health
    cowboy1->shoot(ninja); 
    cowboy2->shoot(ninja);
    cowboy3->shoot(ninja);

    //90 health
    cowboy1->shoot(ninja);
    cowboy2->shoot(ninja);
    cowboy3->shoot(ninja);

    //60 health
    cowboy1->shoot(ninja);
    cowboy2->shoot(ninja);
    cowboy3->shoot(ninja);

    CHECK(ninja->isAlive() == true);

    //30 health
    cowboy1->shoot(ninja);
    cowboy2->shoot(ninja);
    cowboy3->shoot(ninja);

    CHECK(ninja->isAlive() == false);

    delete ninja;
    delete cowboy1;
    delete cowboy2;
    delete cowboy3;
}

TEST_CASE("6. Check reload"){
    YoungNinja* ninja = new YoungNinja("nin-ja", Point(0, 0));
    Cowboy* cowboy = new Cowboy("cow-boy", Point(20, 20));

    for(int i = 0; i < 10;i++){
        cowboy->shoot(ninja);
    }
    CHECK(ninja->isAlive() == true);

    cowboy->shoot(ninja);
    CHECK(ninja->isAlive() == false);

    cowboy->shoot(ninja);
    cowboy->shoot(ninja);
    CHECK(cowboy->hasboolets() == false);
    cowboy->reload();
    CHECK(cowboy->hasboolets() == true);

    delete ninja;
    delete cowboy;
}

TEST_CASE("7. Point printing"){
    Point p1(26.4, 108);
    Point p2(0, 0);
    Point p3(-7, 2);

    CHECK(p1.print() == "{26.4, 108}");
    CHECK(p2.print() == "{0, 0}");
    CHECK(p3.print() == "{-7, 2}");
}

TEST_CASE("8. Character printing"){
    YoungNinja ninja("nin-ja", Point(0, 0));
    CHECK(ninja.print() == "{N:nin-ja, 100, {0, 0}}");

    YoungNinja ninja2("shalom", Point(0, 0));
    CHECK(ninja2.print() == "{N:shalom, 100, {0, 0}}");

    Cowboy cowboy("cow-boy", Point(20, 20));
    cowboy.shoot(&ninja2);
    CHECK(ninja2.print() == "{N:shalom, 90, {0, 0}}");
    CHECK(cowboy.print() == "{C:cow-boy, 110, {20, 20}}");

    while(ninja2.isAlive()){
        cowboy.shoot(&ninja2);
    }

    CHECK(ninja2.print() == "{N:shalom, {0, 0}}");
}

TEST_CASE("9. Team1 printing"){
    Cowboy *c1 = new Cowboy("Tom1", Point(0, 0));
    Cowboy *c2 = new Cowboy("Tom2", Point(0, 0));
    Cowboy *c3 = new Cowboy("Tom3", Point(0, 0));
    OldNinja *n1 = new OldNinja("sushi1", Point(1, 20));
    OldNinja *n2 = new OldNinja("sushi2", Point(1, 20));

    Team team1(c1);
    team1.add(n1);
    team1.add(c2);
    team1.add(c3);
    team1.add(n2);

    string expected = "";
    expected += c1->print() + "\n";
    expected += c2->print() + "\n";
    expected += c3->print() + "\n";
    expected += n1->print() + "\n";
    expected += n2->print() + "\n";

    CHECK(team1.print() == expected);
}

TEST_CASE("10. Team2 printing"){
    Cowboy *c1 = new Cowboy("Tom1", Point(0, 0));
    Cowboy *c2 = new Cowboy("Tom2", Point(0, 0));
    Cowboy *c3 = new Cowboy("Tom3", Point(0, 0));
    OldNinja *n1 = new OldNinja("sushi1", Point(1, 20));
    OldNinja *n2 = new OldNinja("sushi2", Point(1, 20));

    Team2 team1(c1);
    team1.add(n1);
    team1.add(c2);
    team1.add(c3);
    team1.add(n2);

    string expected = "";
    expected += c1->print() + "\n";
    expected += n1->print() + "\n";
    expected += c2->print() + "\n";
    expected += c3->print() + "\n";
    expected += n2->print() + "\n";

    CHECK(team1.print() == expected);
}

TEST_CASE("11. Team fight correct win"){
    Cowboy *c1 = new Cowboy("Tom1", Point(0, 0));
    Cowboy *c2 = new Cowboy("Tom2", Point(0, 0));
    Cowboy *c3 = new Cowboy("Tom3", Point(0, 0));
    OldNinja *n1 = new OldNinja("sushi1", Point(0, 0));
    OldNinja *n2 = new OldNinja("sushi2", Point(0, 0));

    Team2 team1(c1);
    team1.add(n1);
    team1.add(c2);
    team1.add(c3);
    team1.add(n2);

    Cowboy *c1_2 = new Cowboy("Tommy1", Point(0, 0));
    Cowboy *c2_2 = new Cowboy("Tommy2", Point(0, 0));
    Cowboy *c3_2 = new Cowboy("Tommy3", Point(0, 0));

    Team2 team2(c1_2);
    team2.add(c2_2);
    team2.add(c3_2);

    while (team1.stillAlive() > 0 && team2.stillAlive() > 0)
    {
        team2.attack(&team1);
        team1.attack(&team2);
    }
    
    CHECK(team1.stillAlive() == 5);
    CHECK(team2.stillAlive() == 0);
}

TEST_CASE("12. Team adding existing player"){
    Cowboy *c1 = new Cowboy("Tom1", Point(0, 0));
    Cowboy *c2 = new Cowboy("Tom2", Point(0, 0));
    Cowboy *c3 = new Cowboy("Tom3", Point(0, 0));

    Team team1(c1);
    team1.add(c2);
    team1.add(c3);

    CHECK_THROWS(team1.add(c1));
}

TEST_CASE("13. Team attack as empty team"){
    Cowboy *c1 = new Cowboy("Tom1_", Point(0, 0));
    Cowboy *c2 = new Cowboy("Tom2_", Point(0, 0));
    Cowboy *c3 = new Cowboy("Tom3_", Point(0, 0));

    Team team1(c1);
    team1.add(c2);
    team1.add(c3);

    Team team2 = Team();

    CHECK_THROWS(team2.attack(&team1));
}

TEST_CASE("14. Character attacking himself"){
    YoungNinja* n1 = new YoungNinja("nin-ja", Point(20, 20));
    Cowboy* c1 = new Cowboy("cow-boy", Point(20, 20));

    Team team1(n1);
    team1.add(c1);

    CHECK_THROWS(n1->slash(n1));
    CHECK_THROWS(team1.attack(&team1));
}

TEST_CASE("15. Team attacking empty team"){
    Cowboy *c1 = new Cowboy("Tom1", Point(0, 0));
    Cowboy *c2 = new Cowboy("Tom2", Point(0, 0));

    Team team1(c1);
    team1.add(c2);

    Team2 team2 = Team2();

    CHECK_NOTHROW(team1.attack(&team2));
}

TEST_CASE("16. Move doesnt overshoot its targer"){
    Point start(0,0);
    Point end(10,10);
    Point middle = Point::moveTowards(start, end, 100000);

    CHECK(middle == Point(10, 10));
}

TEST_CASE("17 SmartTeam print"){
    Cowboy *c1 = new Cowboy("Tom1", Point(0, 0));
    Cowboy *c2 = new Cowboy("Tom2", Point(0, 0));
    Cowboy *c3 = new Cowboy("Tom3", Point(0, 0));
    OldNinja *n1 = new OldNinja("sushi1", Point(1, 20));
    OldNinja *n2 = new OldNinja("sushi2", Point(1, 20));

    SmartTeam team1(c1);
    team1.add(n1);
    team1.add(c2);
    team1.add(c3);
    team1.add(n2);

    string expected = "";
    expected += c1->print() + "\n";
    expected += n1->print() + "\n";
    expected += c2->print() + "\n";
    expected += c3->print() + "\n";
    expected += n2->print() + "\n";

    CHECK(team1.print() == expected);
}

TEST_CASE("18-1 SmartTeam wins vs Team"){
    Team team1(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));

    team1.add(new YoungNinja("", Point(0, 0)));
    team1.add(new YoungNinja("", Point(0, 0)));
    team1.add(new TrainedNinja("", Point(0, 0)));
    team1.add(new TrainedNinja("", Point(0, 0)));
    team1.add(new OldNinja("", Point(0, 0)));

    SmartTeam team2(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));

    team2.add(new YoungNinja("", Point(150, 150)));
    team2.add(new YoungNinja("", Point(150, 150)));
    team2.add(new TrainedNinja("", Point(150, 150)));
    team2.add(new TrainedNinja("", Point(150, 150)));
    team2.add(new OldNinja("", Point(150, 150)));

    while (team1.stillAlive() > 0 && team2.stillAlive() > 0)
    {
        team2.attack(&team1);
        team1.attack(&team2);
    }

    CHECK(team2.stillAlive() > 0);
}

TEST_CASE("18-2 SmartTeam wins vs Team"){
    Team team1(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));

    team1.add(new YoungNinja("", Point(0, 0)));
    team1.add(new YoungNinja("", Point(0, 0)));
    team1.add(new TrainedNinja("", Point(0, 0)));
    team1.add(new TrainedNinja("", Point(0, 0)));
    team1.add(new OldNinja("", Point(0, 0)));

    SmartTeam team2(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));

    team2.add(new YoungNinja("", Point(150, 150)));
    team2.add(new YoungNinja("", Point(150, 150)));
    team2.add(new TrainedNinja("", Point(150, 150)));
    team2.add(new TrainedNinja("", Point(150, 150)));
    team2.add(new OldNinja("", Point(150, 150)));

    while (team1.stillAlive() > 0 && team2.stillAlive() > 0)
    {        
        team1.attack(&team2);
        team2.attack(&team1);
    }

    CHECK(team2.stillAlive() > 0);
}

TEST_CASE("19-1 SmartTeam wins vs Team"){
    Team2 team1(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));

    team1.add(new YoungNinja("", Point(0, 0)));
    team1.add(new YoungNinja("", Point(0, 0)));
    team1.add(new TrainedNinja("", Point(0, 0)));
    team1.add(new TrainedNinja("", Point(0, 0)));
    team1.add(new OldNinja("", Point(0, 0)));

    SmartTeam team2(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));

    team2.add(new YoungNinja("", Point(150, 150)));
    team2.add(new YoungNinja("", Point(150, 150)));
    team2.add(new TrainedNinja("", Point(150, 150)));
    team2.add(new TrainedNinja("", Point(150, 150)));
    team2.add(new OldNinja("", Point(150, 150)));

    while (team1.stillAlive() > 0 && team2.stillAlive() > 0)
    {
        team2.attack(&team1);
        team1.attack(&team2);
    }

    CHECK(team2.stillAlive() > 0);
}

TEST_CASE("19-2 SmartTeam wins vs Team"){
    Team2 team1(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));
    team1.add(new Cowboy("", Point(0, 0)));

    team1.add(new YoungNinja("", Point(0, 0)));
    team1.add(new YoungNinja("", Point(0, 0)));
    team1.add(new TrainedNinja("", Point(0, 0)));
    team1.add(new TrainedNinja("", Point(0, 0)));
    team1.add(new OldNinja("", Point(0, 0)));

    SmartTeam team2(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));
    team2.add(new Cowboy("", Point(150, 150)));

    team2.add(new YoungNinja("", Point(150, 150)));
    team2.add(new YoungNinja("", Point(150, 150)));
    team2.add(new TrainedNinja("", Point(150, 150)));
    team2.add(new TrainedNinja("", Point(150, 150)));
    team2.add(new OldNinja("", Point(150, 150)));

    while (team1.stillAlive() > 0 && team2.stillAlive() > 0)
    {        
        team1.attack(&team2);
        team2.attack(&team1);
    }

    CHECK(team2.stillAlive() > 0);
}

TEST_CASE("Correct distance calculations"){
    Point p1(10,10);
    Point p2(20,20);
    Point p3(0,0);
    Point p4(20,20);

    CHECK(p1.distance(p2) == sqrt(100 + 100));
    CHECK(p2.distance(p3) == sqrt(400 + 400));
    CHECK(p3.distance(p1) == sqrt(100 + 100));
    CHECK(p2.distance(p2) == sqrt(0));
}