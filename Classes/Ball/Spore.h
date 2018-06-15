
#include "Ball.h"

class Spore : public Ball
{
public:
	Spore();
	~Spore();

	static Spore * create(const std::string& filename);
	bool init(const std::string& filename);

	static Spore * create(int id);
	bool init(int id);

	int getID();
private:
	int _skinID;
};
