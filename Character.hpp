#ifndef CHARACTER_H
#define CHARACTER_H

#include "CharacterAnim.hpp"

class Character
{
	public:
		Character();
		virtual ~Character();

		void Update();
		void Input();

	protected:
	private:
		CharacterAnim anim;
};

#endif // CHARACTER_H
