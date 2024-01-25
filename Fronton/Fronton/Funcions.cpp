//#include "Funcions.h"
////esta en comentari perque no funciona
////brick:
//const int numBricks = 9;	//number of bricks
//RectangleShape brick[numBricks];	//array
//float separation = 150.0f;	//space between bricks
//int main() {
//	for (int i = 0; i < numBricks; ++i)
//	{
//		brick[i].setSize(Vector2f(175.0f, 100.0f));  // Set the size of the rectangle
//		brick[i].setFillColor(Color(192, 218, 46, 250));	// Set the fill color (rgbacolorpicker.com)
//		brick[i].setPosition(50.0f + (50.0f + separation) * i, 20.0f);       // Set the position of the rectangle
//	}
//
//}
//void Draw(RenderWindow& window, Sprite& spriteBackground, CircleShape& bola, Sprite&
//	spritePlayer, Text messageText) {
//		{
//			window.clear();
//			window.draw(spriteBackground);
//
//			window.draw(bola);
//			window.draw(spritePlayer);
//			window.draw(messageText);
//			for (int i = 0; i < numBricks; ++i) //draw bricks
//			{
//				window.draw(brick[i]);
//			}
//			// Show everything we just drew
//			window.display();
//		}
//}