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

		float x;
		float y;

		bool pressingDown;
		bool pressingUp;
		bool pressingLeft;
		bool pressingRight;
};

#endif // CHARACTER_H
