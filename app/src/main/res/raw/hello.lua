text="I am in lua Script\n"
chinese="��������,�޹��� "

function setcontent(view)
    view:setText(text..chinese.."\nthis is setcontent")
    Log:i("LuaLog", "over setcontent")
end

function value(value)
    return 10
end
print "end of lua script"