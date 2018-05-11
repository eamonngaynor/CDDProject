

/*! 


Author: Eamonn Gaynor & Peter Cronin

Date: 04/05/2018

File: main.cpp

Brief: Wator Simulator, optimized using OpenMP

Bugs: N/A

Licence: GNU (General Public License)


*/



#include <iostream>
#include <random>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <cmath>
#include <omp.h>
#include <sys/time.h>
#include <fstream>
    

using namespace std;

char const water = '~'; //water symbol
char const fish = 'O'; //fish symbol
char const shark = 'X'; //shark symbol
int numFish = 16;
int numSharks = 8;
int const width = 30;
int const height = 30;

long int microseconds = 100000; // Timer variable

class Grid {
	public:
		char symbol;
		// Constructor for the water
		Grid() {
			symbol = water;
	   	}
		// Contstructor for types: Fish and Sharks
	   	Grid(char type) {
	  		if (type == fish) {
				symbol = fish;
	   		}
	   		else {
				symbol = shark;
	   		}
		}
};

class Animal {
	public:
		int setX (int x) {
			_x = x;
	   	}

	   	int setY (int y) {
	   		_y = y;
	   	}

	   	int getX () {
	   		return _x;
	   	}

	   	int getY() {
	   		return _y;
	   	}

	   	void moveX (int rX) {
	   		_x = _x + rX;
	   		if(_x > width - 1) {
		        _x = 0;
		    }
		    if(_x < 0) {
		        _x = width - 1;
		    }
	   	}

	   	void moveY (int rY) {
	   		_y = _y + rY;
	   		if(_y > height - 1) {
		        _y = 0;
		    }
		    if(_y < 0) {
		        _y = height - 1;
		    }
	   	}
	protected:
		int _x;
		int _y;
};

class Fish: public Animal {
	public:
		void increaseBreedAge () {
			breedAge++;
		}

		void resetBreedAge () {
			breedAge = 0;
		}

		bool canFishBreed() {
			return canBreed == breedAge;
		}
		int getBreedAge () {
			return breedAge;
		}
	private:
		int canBreed = 5;
		int breedAge = 0;
};

class Shark: public Animal {
	public:
		bool checkNeighbourhood (vector<vector<Grid>> &sea) {
			if (checkLeft(sea) || checkTop(sea) || checkRight(sea) || checkBottom(sea)) {
				return true;
			}
			return false;
		}

		bool checkLeft (vector<vector<Grid>> &sea) {
			// check left side for fish
			if (_x - 1 >= 0) {
				if (sea[_x - 1][_y].symbol == fish) {
					_x = _x - 1;
					increaseEnergy();
					resetHunger();
					return true;
				}
			}
			// check left edge for fish
			if (_x - 1 < 0) {
				if (sea[width - 1][_y].symbol == fish) {
					_x = width - 1;
					increaseEnergy();
					resetHunger();
					return true;
				}
			}
			return false;
		}
		bool checkRight (vector<vector<Grid>> &sea) {
			// check right side for fish
			if (_x + 1 < width) {
				if (sea[_x + 1][_y].symbol == fish) {
					_x = _x + 1;
					increaseEnergy();
					resetHunger();
					return true;
				}
			}
			// check right edge for fish
			if (_x + 1 == width) {
				if (sea[0][_y].symbol == fish) {
					_x = 0;
					increaseEnergy();
					resetHunger();
					return true;
				}
			}
			return false;
		}

		bool checkTop (vector<vector<Grid>> &sea) {
			// check top position for fish
			if (_y - 1 >= 0) {
				if (sea[_x][_y - 1].symbol == fish) {
					_y = _y - 1;
					increaseEnergy();
					resetHunger();
					return true;
				}
			}
			// check top edge for fish
			if (_y - 1 < 0) {
				if (sea[_x][height - 1].symbol == fish) {
					_y = height - 1;
					increaseEnergy();
					resetHunger();
					return true;
				}
			}
			return false;
		}

		bool checkBottom (vector<vector<Grid>> &sea) {
			// check bottom position for fish
			if (_y + 1 < height) {
				if (sea[_x][_y + 1].symbol == fish) {
					_y = _y + 1;
					increaseEnergy();
					resetHunger();
					return true;
				}
			}
			// check bottom edge for fish
			if (_y + 1 == height) {
				if (sea[_x][0].symbol == fish) {
					_y = 0;
					increaseEnergy();
					resetHunger();
					return true;
				}
			}
			return false;
		}

		void increaseEnergy () {
			energy++;
		}

		bool canSharkBreed () {
			return energy == canBreed;
		}

		void resetEnergy () {
			energy = 0;
		}

		void gettingHungry () {
			hunger++;
		}

		bool hasStarved () {
			return hunger == starve;
		}

		void resetHunger () {
			hunger = 0;
		}

		int getEnergy() {
			return energy;
		}
		int	getHunger () {
			return hunger;
		}
	private:
		int canBreed = 3;
		int starve = 20;
		int energy = 0;
		int hunger = 0;
};

//creating the sea grid
void draw(vector<vector<Grid>> &sea) {
	
	for(int i = 0; i < height; i++) {
	//int thread = omp_get_thread_num();
	//std::cout<< "Thread: " <<thread;
    	for(int j= 0; j < width; j++) {
        	cout << sea[j][i].symbol;
        }
 	cout << endl;
    }
    cout << endl;

}

//populate grid with fish
void populateFish(vector<vector<Grid>> &sea, vector<Fish> &fishArray, int numFish) {
    //Checking for available space
    #pragma omp parallel for
    for (int i=0; i < numFish; i++) {
	
    	fishArray[i] = Fish();
    	do {
        	fishArray[i].setX(rand() % width);
        	fishArray[i].setY(rand() % height);
        }
        while (sea[fishArray[i].getX()][fishArray[i].getY()].symbol != water);
    	sea[fishArray[i].getX()][fishArray[i].getY()] = Grid(fish);
    }
}

//populate grid with sharks
void populateSharks(vector<vector<Grid>> &sea, vector<Shark> &sharkArray, int numSharks) {
    #pragma omp parallel for
    for (int i=0; i < numSharks; i++) {
	//int thread = omp_get_thread_num();
	//std::cout<< "\nThread: " <<thread;
    	sharkArray[i] = Shark();
    	do {
    	   	sharkArray[i].setX(rand() % width);
        	sharkArray[i].setY(rand() % height);
        }
        while (sea[sharkArray[i].getX()][sharkArray[i].getY()].symbol != water);
        sea[sharkArray[i].getX()][sharkArray[i].getY()] = Grid(shark);
    }
}

void removeFishObj (vector<Fish> &fishArray, int x, int y) {
	#pragma omp parallel for
	for (int i=0; i < numFish; i++) {
    	if (fishArray[i].getX() == x && fishArray[i].getY() == y) {
    		fishArray.erase(fishArray.begin() + i);
    		numFish--;
    	}
    }
}

// make decision to go left or right and top or bottom
int makeDecision () {
	return rand() % 100 > 50 ? 1 : -1;
}

typedef unsigned long long timestamp_t;

    static timestamp_t
    get_timestamp ()
    {
      struct timeval now;
      gettimeofday (&now, NULL);
      return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
    }



int i = 0;

int main(void) {  

  
	
  #pragma omp parallel
  { //Threads created, concurrency added
    //Segmentation dump on execution as threads not being shared	
  }
	timestamp_t t0 = get_timestamp(); //getting initial timestamp
	
	srand(time(0));
	vector<Fish> fishArray;
	fishArray.resize(numFish);

	vector<Shark> sharkArray;
	sharkArray.resize(numSharks);

    vector<vector<Grid>> sea;
    sea.resize(width);

   
    for( int i = 0; i < width; i++) {
    	sea[i].resize(height);	
    }
    
	populateFish(sea, fishArray, numFish);
	populateSharks(sea, sharkArray, numSharks);

	draw(sea);

	int move = 0;
    while(numFish > 0 && numSharks > 0) {
		//cin.get();
    	int newFish = 0;
    	int blocked = 0;
	
	
    	for (int i=0; i < numFish; i++) {
	
    		int previousX = fishArray[i].getX();
    		int previousY = fishArray[i].getY();
    		makeDecision() < 0 ? fishArray[i].moveX(makeDecision()): fishArray[i].moveY(makeDecision());

			// if next position is free, move fish there
    		if (sea[fishArray[i].getX()][fishArray[i].getY()].symbol == water) {
	        	sea[fishArray[i].getX()][fishArray[i].getY()] = Grid(fish);
				// increase breed age
	        	fishArray[i].increaseBreedAge();
				// when fish can breed, move and add new fish in old position
	        	if (fishArray[i].canFishBreed()) {
	        		newFish++;
	        		fishArray[i].resetBreedAge();
	        		fishArray.resize(numFish + newFish);
	        		fishArray[numFish + newFish - 1] = Fish();
			        fishArray[numFish + newFish - 1].setX(previousX);
			        fishArray[numFish + newFish - 1].setY(previousY);
	        	} else {
	        		sea[previousX][previousY] = Grid();
	        	}
	        } else {
	        	blocked++;
	        	fishArray[i].setX(previousX);
        		fishArray[i].setY(previousY);
				// if fish is blocked don't move
	        	if (blocked < 10) {
	        		continue;
	        	}
	        }
    	}
    	blocked = 0;
    	numFish = numFish + newFish;

    	int newShark = 0;
	
	
    	for (int i=0; i < numSharks; i++) {
    		int previousX = sharkArray[i].getX();
    		int previousY = sharkArray[i].getY();
		// if fish is near, move shark there and eat fish
		//int thread = omp_get_thread_num();
		//std::cout<< "Thread: " <<thread;
		
    		if (sharkArray[i].checkNeighbourhood(sea)) {
    			sea[sharkArray[i].getX()][sharkArray[i].getY()] = Grid(shark);
    			removeFishObj(fishArray, sharkArray[i].getX(), sharkArray[i].getY());
    			numFish = fishArray.size();
				// when shark can breed, move and add new shark in old position
    			if (sharkArray[i].canSharkBreed()) {
    				newShark++;
    				sharkArray[i].resetEnergy();
    				sharkArray.resize(numSharks + newShark);
    				sharkArray[numSharks + newShark -1] = Shark();
    				sharkArray[numSharks + newShark - 1].setX(previousX);
			        sharkArray[numSharks + newShark - 1].setY(previousY);
    			} else {
    				sea[previousX][previousY] = Grid();
    			}
    		} 
		else {
    			makeDecision() < 0 ? sharkArray[i].moveX(makeDecision()): sharkArray[i].moveY(makeDecision());
				// move shark to free position
	    		if (sea[sharkArray[i].getX()][sharkArray[i].getY()].symbol == water) {
		        	sea[previousX][previousY] = Grid();
					// increase hunger
		        	sharkArray[i].gettingHungry();
					// shark has starved
		        	if (sharkArray[i].hasStarved()) {
		        		sharkArray.erase(sharkArray.begin() + i);
		        		numSharks--;
		        	} else {
		        		sea[sharkArray[i].getX()][sharkArray[i].getY()] = Grid(shark);
		        	}
		        } else {
		        	blocked++;
		        	sharkArray[i].setX(previousX);
	        		sharkArray[i].setY(previousY);
					// if shark is blocked don't move
	        		if (blocked < 10) {
	        			sharkArray[i].gettingHungry();
		        		continue;
		        	}
		        }
    		}
	    
    	}
    	numSharks = numSharks + newShark;
    	blocked = 0;

    	move++;
    	timestamp_t t1 = get_timestamp();
    	double secs = (t1 - t0) / 1000000.0L;
    	double fps = move/secs;	
    	std::cout << "\nFPS: " << fps;

    	std::fstream fs;
    	fs.open ("Benchmarking.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    	fs << "  ------ BENCHMARKING -----.\n Frames per second: " << fps;
    	fs.close();


		cout << "\nMove: " << move << endl;
		usleep(microseconds);
    	draw(sea);
		cout << "Fish[" << numFish << "] Sharks[" << numSharks << "]" << endl;
		cout << endl;
	}
    
    timestamp_t t1 = get_timestamp();
    double secs = (t1 - t0) / 1000000.0L;
    double fps = move/secs;	
    std::cout << "\nFPS: " << fps;

    std::fstream fs;
    fs.open ("Benchmarking.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    fs << "  ------ BENCHMARKING -----.\n Time taken to complete " << secs;
    fs.close();

    
}

