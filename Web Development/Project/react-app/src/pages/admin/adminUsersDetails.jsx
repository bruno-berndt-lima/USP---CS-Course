import React, { useState } from 'react';
import './adminUsersDetails.css';
import ChangeUserType from '../../components/ChangeUserType';
import DeleteUser from '../../components/DeleteUser';

const UsersDetails = ({ user, onUserDeleted }) => {
  const [isAdmin, setIsAdmin] = useState(user.admin);

  const handleUserTypeChange = (newAdminValue) => {
    setIsAdmin(newAdminValue);
  };

  const handleUserDeleted = () => {
    onUserDeleted(user._id);
  };


  return (
    <div className="user-preview" key={user._id}>
      <div className="user-name">
        <h2>{user.name}</h2>
        <div className="delete-user-btn">
          <DeleteUser userId={user._id} onUserDeleted={handleUserDeleted}/>
        </div>
      </div>

      <div className="user-email">
        <p>
          <strong>Email: </strong>
          {user.email}
        </p>
      </div>

      <div className="user-cpf">
        <p>
          <strong>CPF: </strong>
          {user.cpf}
        </p>
      </div>

      <div className="user-cellphone">
        {user.phones.map((phone, index) => (
          <p key={index}>
            <strong>Phone {index + 1}: </strong>
            {phone}
          </p>
        ))}
      </div>

      <div className="user-address">
        <p>
          <strong>Address</strong>
        </p>
        {user && user.address ? (
          <React.Fragment key={user.address._id}>
            <p>
              {user.address.street}, {user.address.number}
            </p>
            {user.address.complement && <p>{user.address.complement}</p>}
            <p>{user.address.neighbourhood}</p>
            <p>
              {user.address.city} - {user.address.state}
            </p>
            <p>CEP: {user.address.cep}</p>
            {user.address.additional && <p>{user.address.additional}</p>}
          </React.Fragment>
        ) : null}
      </div>

      <div className="user-type">
        <p>
          <strong>Type </strong>
          {isAdmin ? <p>Admin User</p> : <p>Normal User</p>}
        </p>
        <ChangeUserType
          user={user}
          isAdmin={isAdmin}
          onUserTypeChange={handleUserTypeChange}
        />
      </div>
    </div>
  );
};

export default UsersDetails;
