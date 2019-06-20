package main

/**
 * Manages adding customers to the lines at the Cash registers
 * distributing people to the shortest available line
*/
class Cash(clock:SpeedyClock) : Thread(){
	
	init{
		super.setDaemon(true)
	}
	
	var q1 = line_ups(2,clock)
	var q2 = line_ups(2,clock)
	var q3 = line_ups(2,clock)
	
	override fun run(){
		var t1 = Thread(q1)
		var t2 = Thread(q2)
		var t3 = Thread(q3)
		t1.setDaemon(true)
		t2.setDaemon(true)
		t3.setDaemon(true)
		t1.start()
		t2.start()
		t3.start()
		while(true){
		}
	}
	
	fun add_cust(c:Customer):Boolean{
		if(q1.size<=q2.size && q1.size<=q3.size){
			if(q1.add(c)){
				return true
			}else{
				if(q2.size<=q3.size){
					if(q2.add(c)){
						return true
					}else{
						if(q3.add(c)){
							return true
						}else{
							return false
						}
					}
				}else{
					if(q3.add(c)){
						return true
					}else{
						if(q2.add(c)){
							return true
						}else{
							return false
						}
					}
				}
			}
		}else if(q2.size<=q1.size && q2.size<=q3.size){
			if(q2.add(c)){
				return true
			}else{
				if(q1.size<=q3.size){
					if(q1.add(c)){
						return true
					}else{
						if(q3.add(c)){
							return true
						}else{
							return false
						}
					}
				}else{
					if(q3.add(c)){
						return true
					}else{
						if(q1.add(c)){
							return true
						}else{
							return false
						}
					}
				}
			}
		}else{
			if(q3.add(c)){
				return true
			}else{
				if(q1.size<=q2.size){
					if(q1.add(c)){
						return true
					}else{
						if(q2.add(c)){
							return true
						}else{
							return false
						}
					}
				}else{
					if(q2.add(c)){
						return true
					}else{
						if(q1.add(c)){
							return true
						}else{
							return false
						}
					}
				}
			}
		}
	}	
}