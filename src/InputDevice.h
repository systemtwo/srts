#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

class InputDevice {
	public:
		virtual bool isSelecting() { return false; } //Is selecting units?
		virtual bool isMoving() { return false; } //Is dragging/moving units?
		virtual double getX() { return 0; }
		virtual double getY() { return 0; }
};

#endif //INPUT_DEVICE_H
