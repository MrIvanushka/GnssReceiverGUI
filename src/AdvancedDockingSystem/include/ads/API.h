#ifndef ADS_API_H
#define ADS_API_H

#include <QFlags>
class QWidget;
class QSplitter;

// Always enable "serialization" namespace.
// It is not required for signals and slots.
#define ADS_NAMESPACE_SER_BEGIN namespace ads { namespace serialization {
#define ADS_NAMESPACE_SER_END }}
#define ADS_NS_SER ::ads::serialization

// Width of the native window frame border (based on OS).
#define ADS_WINDOW_FRAME_BORDER_WIDTH 7

// Beautiful C++ stuff.
#define ADS_Expects(cond)
#define ADS_Ensures(cond)

// Indicates whether ADS should include animations.
//#define ADS_ANIMATIONS_ENABLED 1
//#define ADS_ANIMATION_DURATION 150


class ContainerWidget;
class SectionWidget;

enum DropArea
{
	InvalidDropArea = 0,
	TopDropArea = 1,
	RightDropArea = 2,
	BottomDropArea = 4,
	LeftDropArea = 8,
	CenterDropArea = 16,

	AllAreas = TopDropArea | RightDropArea | BottomDropArea | LeftDropArea | CenterDropArea
};
Q_DECLARE_FLAGS(DropAreas, DropArea)

void deleteEmptySplitter(ContainerWidget* container);
ContainerWidget* findParentContainerWidget(QWidget* w);
SectionWidget* findParentSectionWidget(QWidget* w);
QSplitter* findParentSplitter(QWidget* w);
QSplitter* findImmediateSplitter(QWidget* w);


#endif
