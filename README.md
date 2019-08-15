# UE4ParentSocket
Parent socket name wrapper with convenient property editing widget. Property editing widget allows for choosing socket name from parent scene component of the scene component containing the parent socket variable.

## Setup

- Place ParentSocket.h header file in a `Runtime` module of your choosing.
- Place contents of Editor folder in a `Editor` module of your choosing.
- Add `FParentSocketCustomization::Register()` call to `StartupModule()` function.
- Add `FParentSocketCustomization::Unregister()` call to `ShutdownModule()` function.

## Usage

- Use `FParentSocket` struct instead of `FName` for socket name. This will work only for a variable in a scene component that is attached to a scene component you want to get socket names from.
- In the Editor in Details view of the component you'll see a combobox widget for editing your socket. You can:
	- select a socket name by clicking on the triangle on the right side of the widget,
	- edit name using keyboard after clicking on the text part of the widget.
