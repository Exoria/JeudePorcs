#ifndef CHARACTER_H
#define CHARACTER_H

#include "CharacterAnim.hpp"
#include "Map.hpp"

class Character
{
	public:
		Character(Map* m);
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

		const Map* _map;

		void MoveFrom(float colx, float coly);
		bool IsCellFree(int cx, int cy);
};

#endif // CHARACTER_H
