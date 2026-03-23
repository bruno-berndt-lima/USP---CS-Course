from contato import pPhysical, pJuridical

class ContactBook:
    def __init__(self):
        contactList = []
        pPhysicalList = []
        pJuridicalList = []

        while True:
            print("Escolha o número da opção desejada:")
            print("1: Adicionar contato")
            print("2: Remover contato")
            print("3: Procurar contato")
            print("4: Mostrar lista de contatos")
            print("5: Sair")

            option = int (input())

            if(option == 1):
                personType = input("Digite 0 se deseja adicinar uma pessoa fisica ou 1 uma pessoa juridica\n")
                if(personType == "0"):
                    ContactBook.add(pPhysicalList, personType)
                elif(personType == "1"):
                    ContactBook.add(pJuridicalList, personType)
                    
            elif(option == 2):
                personType = input("Digite 0 se deseja remover uma pessoa fisica ou 1 uma pessoa juridica\n")
                if(personType == "0"):
                    ContactBook.remove(pPhysicalList, personType)
                elif(personType == "1"):
                    ContactBook.remove(pJuridicalList, personType)

            elif(option == 3):
                personType = input("Digite 0 se deseja buscar uma pessoa fisica ou 1 uma pessoa juridica\n")
                if(personType == "0"):
                    ContactBook.search(pPhysicalList, personType)
                elif(personType == "1"):
                    ContactBook.search(pJuridicalList, personType)

            elif(option == 4):
                ContactBook.show(contactList)

            else:
                break

            contactList = ContactBook.getSortedContacts(pPhysicalList, pJuridicalList)

    def add(list, personType):
        print("Digite os dados da pessoa que deseja adicionar")
        name = input("Name: ")
        address = input("Address: ")
        birthDate = input("Birth Date: ")
        email = input("Email: ")

        if(personType == "0"):
            cpf = input("CPF: ")
            maritalStatus =  input("Marital Status: ")
            p = pPhysical(name, address, birthDate, email, cpf, maritalStatus)
            list.append(p)
            return
        
        elif(personType == "1"):
            cnpj = input("CNPJ: ")
            stateReg = input("State Registration: ")
            corpName = input("Corporate Name: ")
            p = pJuridical(name, address, birthDate, email, cnpj, stateReg, corpName)
            list.append(p)
            return
  
    def remove(list, personType):
        if(personType == "0"):
            cod = input("Digite o CPF da pessoa que deseja remover\n")
            for index,  p in enumerate(list):
                if(p.cpf == cod):   
                    del list[index]
                    return
        
        elif(personType == "1"):
            cod = input("Digite o CNPJ da pessoa que deseja remover\n")
            for index,  p in enumerate(list):
                if(p.cnpj == cod):   
                    del list[index]
                    return
        
        print("Não removeu! Pessoa não encontrada.\n") 
        return

                    
    def search(list, personType):
        if(personType == "0"):
            searchType = input("Como deseja fazer a busca? Digite \"NOME\" ou \"CPF\"\n")
            if(searchType == "NOME"):
                name = input("Digite o nome da pessoa que deseja procurar\n")
                for p in list:
                    if(p.name == name):   
                        p.show()
                        return
        
            elif(searchType == "CPF"):
                cpf = input("Digite o cpf da pessoa que deseja procurar\n")
                for p in list:
                    if(p.cpf == cpf):   
                        p.show()
                        return
        
        elif(personType == "1"):
            searchType = input("Como deseja fazer a busca? Digite \"NOME\" ou \"CNPJ\"\n")
            if(searchType == "NOME"):
                name = input("Digite o nome da pessoa que deseja procurar\n")
                for p in list:
                    if(p.name == name):   
                        p.show()
                        return
               
            elif(searchType == "CNPJ"):
                cnpj = input("Digite o cnpj da pessoa que deseja procurar\n")
                for p in list:
                    if(p.cnpj == cnpj):   
                        p.show()
                        return

        print("Pessoa não encontrada.\n") 
        return  
            
    def sortPhysicalList(list):
        for i in range(len(list)):
            for j in range(0, (len(list) - i - 1)):
                if list[j].cpf > list[j + 1].cpf:
                    (list[j], list[j + 1]) = (list[j + 1], list[j])
    
    def sortJuridicalList(list):
        for i in range(len(list)):
            for j in range(0, (len(list) - i - 1)):
                if list[j].cnpj > list[j + 1].cnpj:
                    (list[j], list[j + 1]) = (list[j + 1], list[j])

    def getSortedContacts(physicalList, juridicalList):
        ContactBook.sortPhysicalList(physicalList)
        ContactBook.sortJuridicalList(juridicalList)

        return physicalList + juridicalList
           
    def show(list):
        if(list):
            for p in list:
                p.show()
            return
        print("Lista de contatos vazia.\n")


ContactBook()