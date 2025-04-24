// const handleSubmit = async (e) => {
//   console.log(e)
//   if(!formValues.firstName || !formValues.lastName || !formValues.cpf || !headerUser.email || !formValues.password ||!formValues.phone || !formValues.zipCode || !formValues.zipCode || !formValues.state || !formValues.neighborhood || !formValues.address || !formValues.number) {
//     alert("Erro");
//     return;
//   }
//   e.preventDefault();
//   const newUser = {
//       name: formValues.firstName + " " + formValues.lastName,
//       cpf: formValues.cpf,
//       email: headerUser.email,
//       password: formValues.password,
//       phones: [
//         formValues.phone,
//         formValues.otherPhone
//       ],
//       address: {
//         cep: formValues.zipCode,
//         city: formValues.zipCode,
//         state: formValues.state,
//         neighbourhood: formValues.neighborhood,
//         street: formValues.address,
//         number: formValues.number,
//         complement: formValues.complement,
//         additional: formValues.referencePoint
//       },
//       cart: [],
//       admin: false
//   }
  
//   const jsonData = JSON.stringify(newUser);

//   const createUser = async () => {
//     try {
//       const response = await fetch('http://localhost:7000/users', {
//         method: 'POST',
//         headers: {
//           'Content-Type': 'application/json',
//         },
//         body: jsonData,
//       });

//       if(response.ok) {
//         const data = await response.json();

//         if(data.ok) {
//           console.log(data)
//         }
//       }
//     } catch (error) {
//       console.log(error)
//     }
//   }

//   await createUser();

//   setHeaderUser({...headerUser, email:""});
//   alert("Account created!")
//   navigate('/')
// };
import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { useForm } from "react-hook-form";
import Footer from '../../components/Footer';
import Header from '../../components/Header';
import './signup.css';

const Signup = ({ headerUser, setHeaderUser}) => {
  const navigate = useNavigate();

  const { register, handleSubmit, formState: {errors} } = useForm();

  const onSubmit = async data => {
    const newUser = {
      name: data.firstName + " " + data.lastName,
      cpf: data.cpf || "",
      email: headerUser.email || "",
      password: data.password || "",
      phones: [
        data.phone,
        data.otherPhone
      ],
      address: {
        cep: data.zipCode || "",
        city: data.city || "",
        state: data.state || "",
        neighbourhood: data.neighborhood || "",
        street: data.street || "",
        number: data.number || "",
        complement: data.complement || "",
        additional: data.referencePoint || ""
      },
      cart: [],
      admin: false
    }

    const jsonData = JSON.stringify(newUser);

    const createUser = async () => {
      try {
        const response = await fetch('http://localhost:7000/users', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: jsonData,
        });
  
        if(response.ok) {
          const data = await response.json();

          if(data.ok) {
            console.log(data)
          }
        }
      } catch (error) {
        console.log(error)
      }
    }

    await createUser();
    console.log(newUser);

    setHeaderUser({...headerUser, email:""});
    alert("Account created!")
    navigate('/')

  }


  

  return (
    <>
      <Header user={headerUser} logged={headerUser.logged} />
      <div className="container">
        <div className="signup-container">
          <h3>*Campos Obrigatórios.</h3>
          <form onSubmit={handleSubmit(onSubmit)}>
            <div className="name-input input-container">
              <input {...register("firstName", {required: "First name is required"})} placeholder='*First Name' type="text" />
              <p>{errors.firstName?.message}</p>
              <input {...register("lastName", {required: "Last name is required"})} placeholder='*Last Name' type="text" />
              <p>{errors.lastName?.message}</p>
            </div>
            <div className="social-information-input input-container">
              <input {...register("cpf", {required: "CPF is required"})} placeholder='*CPF' type="number" />
              <p>{errors.cpf?.message}</p>
            </div>
            <div className="phone-inputs input-container">
              <input {...register("phone", {required: "Phone is required"})} placeholder='Phone' type="tel" />
              <p>{errors.phone?.message}</p>
              <input {...register("otherPhone")} placeholder='Other Phone' type="tel" />
            </div>
            <div className="address-input input-container">
              <input {...register("street", {required: "Street is required"})} placeholder='*Street' type="text" />
              <p>{errors.street?.message}</p>
            </div>
            <div className="zip-neighbour-input input-container">
              <input {...register("zipCode", {required: "CEP is required"})} placeholder='*CEP' type="number" />
              <p>{errors.cpf?.message}</p>
              <input {...register("neighborhood", {required: "Neighborhood is required"})} placeholder='*Bairro' type="text" />
              <p>{errors.neighborhood?.message}</p>
            </div>
            <div className="additional-address-input input-container">
              <input {...register("number", {required: "Number is required"})} placeholder='*Numero' type="number" />
              <p>{errors.number?.message}</p>
              <input {...register("complement")} placeholder='Complemento' type="text" />
            </div>
            <div className="city-info-input input-container">
              <input {...register("city", {required: "City is required"})} placeholder='*Cidade' type="text" />
              <p>{errors.city?.message}</p>
              <select {...register("state", {required: "State is required"})}>
                <option value='' disabled selected>*UF</option>
                <option value='AC'>AC</option>
                <option value='AL'>AL</option>
                <option value='AP'>AP</option>
                <option value='AM'>AM</option>
                <option value='BA'>BA</option>
                <option value='CE'>CE</option>
                <option value='DF'>DF</option>
                <option value='ES'>ES</option>
                <option value='GO'>GO</option>
                <option value='MA'>MA</option>
                <option value='MT'>MT</option>
                <option value='MS'>MS</option>
                <option value='MG'>MG</option>
                <option value='PA'>PA</option>
                <option value='PB'>PB</option>
                <option value='PR'>PR</option>
                <option value='PE'>PE</option>
                <option value='PI'>PI</option>
                <option value='RJ'>RJ</option>
                <option value='RN'>RN</option>
                <option value='RS'>RS</option>
                <option value='RO'>RO</option>
                <option value='RR'>RR</option>
                <option value='SC'>SC</option>
                <option value='SP'>SP</option>
                <option value='SE'>SE</option>
                <option value='TO'>TO</option>
              </select>
            </div>
            <div className="reference-point input-container">
              <input {...register("referencePoint")} placeholder='Ponto de Referencia' type="text" />
            </div>

            <div className="password input-container">
              <input {...register("password", {required: "Password is required"})} placeholder='*Senha' type="password" />
              <p>{errors.password?.message}</p>
            </div>

            <div className="submit-button">
              <input type="submit" value="Submit" />
            </div>
          </form>
        </div>
      </div>

      <Footer />
    </>
  );
};

export default Signup;
