package main

/**
 * A time class designed to track some basic data on Time for user with the SpeedyCLock
 * 
*/
class Time() {
	
	constructor(hrs:Int,mins:Int,secs:Int):this(){
		this.hr=hrs
		this.min=mins
		this.sec=secs
	}
	
	var sec:Int = 0
	var min:Int = 0
	var hr:Int = 0
	
	fun to_sec():Int{
		return hr*60*60+min*60+sec
	}
	
}