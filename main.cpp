#include "bouncer.h"

int main(int argc, char** argv) {
    Bouncer bouncer(argc, argv);
    bouncer.move();

	//level_1
	bouncer.addLevel([&]() {
		bouncer.horizontal_line(-10, 20, -1);
		bouncer.vertical_line(2, 0, 2);
		bouncer.vertical_line(6, 0, 1);
		bouncer.loseBlock(6, 2);
		bouncer.vertical_line(12, 0, 3);
		bouncer.winBlock(20, 2);
	});
	//level_2
    bouncer.addLevel([&]()
    {
        bouncer.horizontal_line(-10,5, -1);
        bouncer.vertical_line(3, 0, 2);
        bouncer.loseBlock(7, 5);
        bouncer.horizontal_line(5, 8, -3);
        bouncer.horizontal_line(8,12, -1);
        bouncer.vertical_line(10, 0, 3);
        bouncer.horizontal_line(10,13, 2);
        bouncer.vertical_line(13, 2, 4);

        bouncer.square(15,16,4,4);
        bouncer.loseBlock(17, 6);
        bouncer.square(18,19,3,3);
        bouncer.square(21,22,2,2);

        bouncer.horizontal_line(22,40, -1);
        bouncer.vertical_line(26, 0, 2);
        bouncer.vertical_line(27, 0, 3);
        bouncer.vertical_line(28, 0, 4);
        bouncer.vertical_line(29, 0, 5);
        bouncer.vertical_line(31, 2, 5);
        bouncer.horizontal_line(31, 35, 2);
        bouncer.vertical_line(40, 0, 6);
        bouncer.horizontal_line(37, 40, 2);
        bouncer.horizontal_line(40, 50,5);
        bouncer.square(43,46,6,6);
        bouncer.loseBlock(45, 7);
        bouncer.winBlock(50, 6);
    });
    //level_3
    bouncer.addLevel([&](){
        bouncer.horizontal_line(-10, 5, -1);
        bouncer.horizontal_line(6, 10, 2);
         bouncer.loseBlock(9, 3);
         bouncer.loseBlock(9, 4);
        bouncer.horizontal_line(11, 13, 2);
         bouncer.loseBlock(14, 3);
         bouncer.loseBlock(14, 4);
        bouncer.horizontal_line(15, 17, 3);
        bouncer.horizontal_line(19, 21, 2);
        bouncer.horizontal_line(23, 25, 1);
        bouncer.horizontal_line(26, 37, -1);
        bouncer.horizontal_line(26, 35, 3);
         bouncer.loseBlock(30, 4);
         bouncer.loseBlock(30, 5);
        bouncer.vertical_line(37, 0, 4);
        bouncer.horizontal_line(37, 40,4);
         bouncer.loseBlock(37, 6);
        bouncer.horizontal_line(42, 43,2);
        bouncer.horizontal_line(45, 46,6);
        bouncer.horizontal_line(48, 49,7);

        bouncer.horizontal_line(49, 55, 3);
        bouncer.vertical_line(50,3,7);
        bouncer.horizontal_line(58, 60, 3);
        bouncer.vertical_line(54,3,5);
        bouncer.loseBlock(38, 6);
        bouncer.horizontal_line(61,65,-1);
        bouncer.loseBlock(53, 4);
        bouncer.horizontal_line(66,70,2);
        bouncer.loseBlock(68, 3);
        bouncer.loseBlock(68, 4);
        bouncer.horizontal_line(72,76,4);
        bouncer.horizontal_line(78,80,6);
        bouncer.winBlock(80,8);

    });
    //level_4
    bouncer.addLevel([&](){
        bouncer.horizontal_line(-8, 5, -1);
        bouncer.vertical_line(-8, 0, 6);
        bouncer.horizontal_line(-8, 5, 6);
        bouncer.vertical_line(5,3,6);
        bouncer.horizontal_line(-3, 5, 3);
        bouncer.horizontal_line(6, 8, -4);
        bouncer.horizontal_line(9, 11, -1);
        bouncer.horizontal_line(12, 14, 1);
        bouncer.horizontal_line(15, 20, 3);
        bouncer.loseBlock(17, 4);
        bouncer.loseBlock(17, 5);
        bouncer.vertical_line(22,3,6);
        bouncer.vertical_line(24,3,7);
        bouncer.vertical_line(26,3,8);
        bouncer.horizontal_line(29, 33, 3);
        bouncer.vertical_line(31,3,7);
        bouncer.horizontal_line(36, 40, 3);
        bouncer.vertical_line(38,3,5);
        bouncer.loseBlock(38, 6);
        bouncer.horizontal_line(41,45,-1);
        bouncer.loseBlock(43, 0);
        bouncer.horizontal_line(46,48,2);
        bouncer.horizontal_line(49,51,4);
        bouncer.horizontal_line(52,54,6);
        bouncer.winBlock(54,8);
    });
    //level_5
    bouncer.addLevel([&](){
        bouncer.horizontal_line(-10,4,-1);
        bouncer.vertical_line(6,0,2);
        bouncer.vertical_line(8,0,3);
        bouncer.loseBlock(8, 4);
        bouncer.vertical_line(10,0,4);
        bouncer.vertical_line(12,0,5);
        bouncer.loseBlock(12, 6);
        bouncer.vertical_line(14,0,4);
        bouncer.vertical_line(16,0,3);
        bouncer.loseBlock(16, 4);
        bouncer.vertical_line(18,0,2);
        bouncer.horizontal_line(20,25,-1);
        bouncer.loseBlock(23, 0);
        bouncer.vertical_line(27,-2,0);
        bouncer.vertical_line(29,-3,-1);
        bouncer.loseBlock(29,0);
        bouncer.vertical_line(31,-4,-2);
        bouncer.vertical_line(33,-5,-3);
        bouncer.loseBlock(33, -2);
        bouncer.vertical_line(35,-4,-2);
        bouncer.vertical_line(37,-3,-1);
        bouncer.loseBlock(37, -0);
        bouncer.vertical_line(39,-2,0);
        bouncer.horizontal_line(41,55,1);
        bouncer.add(43,2);
        bouncer.horizontal_line(44,55,4);
        bouncer.vertical_line(55,3,4);
        bouncer.winBlock(55,2);

    });
    //level_6
    bouncer.addLevel([&]() {
        bouncer.horizontal_line(-5, 5, -1);
        bouncer.vertical_line(-6, -1, 10);
        bouncer.horizontal_line(3, 10, -20);
        bouncer.loseBlock(11, -20);
        bouncer.loseBlock(11, -19);
        bouncer.loseBlock(11, -18);
        bouncer.loseBlock(11, -17);
        bouncer.loseBlock(11, -13);
        bouncer.loseBlock(11, -12);
        bouncer.loseBlock(11, -11);
        for (int i = 0; i < 10; ++i) {
            bouncer.loseBlock(11 + i, -12);
        }
        bouncer.horizontal_line(10, 16, -25);;
        bouncer.vertical_line(17, -25, -20);
        bouncer.vertical_line(18, -25, -20);
        bouncer.vertical_line(19, -25, -20);
        bouncer.loseBlock(18, -19);
        bouncer.loseBlock(19, -19);
        bouncer.loseBlock(20, -19);
        bouncer.vertical_line(20, -25, -20);
        bouncer.vertical_line(21, -25, -20);
        bouncer.vertical_line(22, -25, -17);
        bouncer.vertical_line(23, -25, -17);
        bouncer.vertical_line(24, -25, -17);
        bouncer.horizontal_line(25, 30, -19);
        bouncer.horizontal_line(33, 51, -15);
        for(int i = 0; i < 5; ++i) {
            bouncer.loseBlock(37 + i * 3, -14);
            bouncer.loseBlock(37 + i * 3, -13);
            bouncer.loseBlock(37 + i * 3, -12);
        }
        bouncer.horizontal_line(55, 68, -15);
        for (int i = 0; i < 9; ++i) {
            bouncer.loseBlock(59 + i, -14);
        }
        bouncer.horizontal_line(60, 66, -13);
        for (int i = 0; i < 5; ++i) {
            bouncer.loseBlock(61 + i, -12);
        }
        bouncer.horizontal_line(62, 64, -11);


        bouncer.loseBlock(56, -14);
        bouncer.loseBlock(56, -13);
        bouncer.loseBlock(56, -12);


        bouncer.winBlock(63, -10);
    });

    bouncer.play();
    return 0;
}


