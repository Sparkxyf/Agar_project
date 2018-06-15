

#include "Ball.h"

class Prick : public Ball
{
public:
	Prick();
	~Prick();

	static Prick * create(const std::string& filename);
	bool init(const std::string& filename);
};

