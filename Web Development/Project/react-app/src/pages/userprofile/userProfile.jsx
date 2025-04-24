import React, { useState } from 'react';
import { useNavigate, useParams } from 'react-router-dom';

import Header from '../../components/Header';
import Footer from '../../components/Footer';

import './userProfile.css';
import '../../App.css';

const UserProfile = ({headerUser, setHeaderUser}) => {
    const key = useParams();

    const user = headerUser;

    const navigate = useNavigate();

    const [logged, setLogged] = useState(headerUser.logged);

    const handleLeave = async () => {
        const newState = {
            id: null,
            name: '',
            email: '',
            password: '',
            logged: false,
            cart: [],
            admin: false,
            address: [],
            phones: []
        }

        const updateCart = async () => {
            try {
                const response = await fetch(`http://localhost:7000/users/${headerUser._id}`, {
                    method: 'PUT',
                    headers: {
                        'Content-Type': 'application/json',
                    },
                    body: JSON.stringify(headerUser),
                })
                // Caso a atualização receba ok
                if(response.ok) {
                    console.log('Client updated successfully');
                } else {
                console.log('Client update failed');
                }
            }
            catch (error){
                console.log(error);
            }
        };

        await updateCart();

        setHeaderUser(newState)
        setLogged(false)
        navigate('/', {replace: true})
    }

    if(headerUser.logged && headerUser._id == key.id) {
        return (  
            <>
                <Header user={headerUser} logged={logged}/>
                    <div className="container-profile-background">
                
                        <div className="container-profile">
                            <span className="profile-title">Seus Dados</span>
                            <div className="form-container">

                                <form>
                                    <div className="form-row">
                                        <div className="form-group-name">
                                            <label htmlFor="name">Nome Completo:</label>
                                            <input type="text" id="name" name="name" value={headerUser.name} required disabled/>
                                        </div>
                                    </div>

                                    <div className="form-row">
                                        {/* <div className="form-group-date">
                                            <label htmlFor="dob">Data de Nascimento:</label>
                                            <input type="date" id="dob" name="dob" required />
                                        </div> */}

                                        <div className="form-group-cpf">
                                            <label htmlFor="cpf">CPF:</label>
                                            <input type="text" id="cpf" name="cpf" value={headerUser.cpf} required disabled/>
                                        </div>

                                    </div>


                                    <div className="form-row">
                                        {headerUser.phones.map(e => {
                                            return (
                                                <div className='form-group-phone'>
                                                    <label>Telefone</label>
                                                    <input type='tel' id={e} name={e} value={e} required disabled></input>
                                                </div>
                                            )
                                        })}
                                        {/* <div className="form-group-phone">
                                            <label htmlFor="phone1">Telefone 1:</label>
                                            <input type="tel" id="phone1" name="phone1" required />
                                        </div>

                                        <div className="form-group-phone">
                                            <label htmlFor="phone2">Telefone 2:</label>
                                            <input type="tel" id="phone2" name="phone2" />
                                        </div> */}
                                    </div>  


                                    <div className="form-row">
                                        <div className="form-group-address">
                                            <label>Endereço</label>
                                            <input type="text" id="endereco" name="endereco" value={headerUser.address.street} required disabled/>
                                        </div>

                                        <div className="form-group-cep">
                                            <label>CEP</label>
                                            <input type="text" id="cep" name="cep" value={headerUser.address.cep} required disabled/>
                                        </div>
                                    </div>

                                    <div className="form-row">
                                        <div className="form-group-bairro">
                                            <label>Bairro</label>
                                            <input type="text" id="bairro" name="bairro" value={headerUser.address.neighbourhood} required disabled/>
                                        </div>

                                        <div className="form-group-complemento">
                                            <label>Complemento</label>
                                            <input type="text" id="complemento" name="complemento" value={headerUser.address.addittional} required disabled/>
                                        </div>
                                    </div>

                                    <div className="form-row">

                                        <div className="form-group-cidade">
                                            <label>Cidade</label>
                                            <input type="text" id="cidade" name="cidade" value={headerUser.address.city} required disabled/>
                                        </div>

                                        <div className="form-group-estado">
                                            <label>Estado</label>
                                            <input type="text" id="estado" name="estado" value={headerUser.address.state} required disabled/>
                                        </div>

                                        <div className="form-group-numero">
                                            <label>Numero</label>
                                            <input type="number" id="numero" name="numero" value={headerUser.address.number} required disabled/>
                                        </div>                                    
                                    </div>

                                    {/*
                                    <div className="form-row">
                                        <div className="form-group-submit">
                                            <input type="submit" value="SALVAR INFORMAÇÕES" />
                                        </div>
                                    </div>
                                    */}   

                                </form>
                            </div>


                            
                            {/*
                            <span className="profile-title">Endereços</span>
                            <div className="addresses-container">
                                <UserAddress headerUser={headerUser} main={true}/>
                                <UserAddress main={false}/> 
                                <div className="form-group-submit btn-save-address">
                                    <input type="submit" value="ADICIONAR NOVO ENDEREÇO" />
                                </div>
                            </div>
                            
                            <div className="leave-container">
                                <input onClick={handleLeave} type="submit" value="SAIR" />
                            </div>
                            */}

                            <div className="leave-container">
                                <input onClick={handleLeave} type="submit" value="SAIR" />
                            </div>


                        </div>                    
                    </div>
                <Footer/>

                
            </>
        );
    } else {
        return (
            <>
                {navigate('/', {replace: true})}
            </>
        )
    }
}
 
export default UserProfile;