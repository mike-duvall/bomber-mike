#include "Timer.h"


#include "SimpleGameObject.h"
#include "Number.h"

Timer::Timer(int x, int y)
{

	emptyTimerShell = new SimpleGameObject(x,y,66,18,"bitmaps/InGame/Scoreboard/BlankTime.bmp",1);
	int numberY = y + 0;
	minutes = new Number(x + 1,numberY );
	tensOfSeconds = new Number(x + 30,numberY );
	seconds = new Number(x + 48,numberY );

	minutes->SetValue(9);
	tensOfSeconds->SetValue(1);
	seconds->SetValue(6);

	countdownIntervalInitialValue = 60;
	countdownInterval = countdownIntervalInitialValue;

	hasExpired = FALSE;

}




void  Timer::Draw(LPDIRECTDRAWSURFACE7 dest)
{
	emptyTimerShell->Draw(dest);
	minutes->Draw(dest);
	tensOfSeconds->Draw(dest);
	seconds->Draw(dest);


}


boolean Timer::Expired()
{

	return hasExpired;
}

void Timer::Update()
{
	if(countdownInterval > 0)
	{
		countdownInterval--;
	}
	else
	{
		countdownInterval = countdownIntervalInitialValue;
		int secondsValue = seconds->GetValue();
		secondsValue--;
		if(secondsValue < 0)
		{
			secondsValue = 9;
			int tensOfSecondsValue = tensOfSeconds->GetValue();
			tensOfSecondsValue--;
			if(tensOfSecondsValue < 0)
			{
				tensOfSecondsValue = 5;
				int minutesValue = minutes->GetValue();
				minutesValue--;
				if(minutesValue < 0)
				{
					minutesValue = 0;
					hasExpired = TRUE;

				}
				minutes->SetValue(minutesValue);
			}
			tensOfSeconds->SetValue(tensOfSecondsValue);
			

		}
		seconds->SetValue(secondsValue);

	}

}