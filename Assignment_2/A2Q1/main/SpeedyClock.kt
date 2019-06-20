package main

/**
 * Simulates a clock in it's own thread using
 * for-loops and thread sleeps to allow a set time to pass
 * at a faster rate then the real world
*/
class SpeedyClock(length:Int):Thread(){
	var time = Time()
	var tot_min:Int = 0
	var l = length
	
	override fun run(){
		while(true){
			for(i in 0..23){
				time.min=0
				time.hr=i
				tot_min = time.hr*60 + time.min
				if(tot_min>=l){
					return
				}
				for(j in 0..59){
					time.sec=0
					time.min=j
					tot_min = time.hr*60 + time.min
					if(tot_min>=l){
						return
					}
					for(k in 0..59){
						//println("" + i + ':' + j + ':'+ k)
						time.sec = k
						Thread.sleep(1)
					}
					time.sec=0
					time.min++
					tot_min = time.hr*60 + time.min
					if(tot_min>=l){
						if(time.min==60){
							time.hr++
							time.min=0
							return
						}
						return
					}
				}
				time.min=0
				time.hr++
				tot_min = time.hr*60 + time.min
				if(tot_min>=l){
					return
				}
			}
		}
	}
	
	fun get_time():Time{
		return Time(time.hr,time.min,time.sec)
	}
}


fun main(args:Array<String>){
		var cl = SpeedyClock(60)
		cl.run()
		cl.join();
		println(""+cl.time.hr+':'+cl.time.min+':'+cl.time.sec);
}