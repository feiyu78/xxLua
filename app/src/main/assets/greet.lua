greet = {}
function greet.hello(name)
	print('Hello '..name..'!')
end


Log:i("lua","---------")
system.init()
Log:i("lua",os.time())
system.sleep(1)
system.click(300, 300)
