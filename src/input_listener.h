#ifndef INPUT_LISTENER_H
#define INPUT_LISTENER_H

/**
 * This class is used as a base class for classes that want
 * to subscribe to input events.
 *
 * The *Pressed() methods are called at the moment the input becomes true.
 * In electronics terms this would be at the rising edge.
 *
 * The *Released() methods are called at the moment the input becomes false.
 * In electronics terms this would be at the falling edge.
 */
class InputListener
{
public:
    virtual ~InputListener() {};

    virtual void leftPressed() {};
    virtual void leftReleased() {};

    virtual void rightPressed() {};
    virtual void rightReleased() {};

    virtual void upPressed() {};
    virtual void upReleased() {};

    virtual void downPressed() {};
    virtual void downReleased() {};

    virtual void buttonPressed() {};
    virtual void buttonReleased() {};
};

#endif // INPUT_LISTENER_H
