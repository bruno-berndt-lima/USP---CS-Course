class Contact:
    def __init__(self, name, adress, birthDate, email):
        self.name = name
        self.address = adress
        self.birthDate = birthDate
        self.email = email

    def show(self):
        print("---------------------")
        print(self.name)
        print(self.address)
        print(self.birthDate)
        print(self.email)
        print("---------------------")


class pPhysical(Contact):
    def __init__(self, name, address, birthDate, email, cpf, maritalStatus):
        super().__init__(name, address, birthDate, email)
        self.cpf = cpf
        self.maritalStatus = maritalStatus

    def show(self):
        print("---------------------")
        print(self.name)
        print(self.address)
        print(self.birthDate)
        print(self.email)   
        print(self.cpf)
        print(self.maritalStatus)
        print("---------------------")


class pJuridical(Contact):
    def __init__(self, name, address, birthDate, email, cnpj, stateReg, corporateName):
        super().__init__(name, address, birthDate, email)
        self.cnpj = cnpj
        self.stateReg = stateReg  
        self.corporateName = corporateName

    def show(self):
        print("---------------------")
        print(self.name)
        print(self.address)
        print(self.birthDate)
        print(self.email)   
        print(self.cnpj)
        print(self.stateReg)
        print(self.corporateName)
        print("---------------------")


