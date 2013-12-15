#ifndef CHARACTER_H
#define CHARACTER_H

#include "CharacterAnim.hpp"

class Character
{
	public:
		Character();
		virtual ~Character();

		void Update(const float deltaT);
		void Draw();
		void Input(const ALLEGRO_EVENT& ev);

	protected:
	private:
		CharacterAnim anim;

		bool pressingUp;
		bool pressingDown;
		bool pressingLeft;
		bool pressingRight;

		float x;
		float y;
};

#endif // CHARACTER_H
