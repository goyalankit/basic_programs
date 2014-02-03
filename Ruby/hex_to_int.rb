class String
    def to_d
        self.to_i(16).to_s(10) #convert hex(16) to decimal(10)
    end
    
    #hex to int
    "0xff".to_d #255
end
