#pragma once
#include <complex>
#include <iostream>
using namespace std;
class H_Item
{
public:
	H_Item()
	{
		Transmitter_Set = 0;
		Receiver_Set = 0;
		Transmitter_Pt = 0;
		Receiver_Pt = 0;
		Transmitter_Element = 0;
		Receiver_Element = 0;
		value = complex(0, 0);
	}
	H_Item(unsigned Tx_Set, unsigned Rx_Set, unsigned Tx_Pt, unsigned Rx_Pt, unsigned Rx_Ele, unsigned Tx_Ele)
	{
		Transmitter_Set = Tx_Set;
		Receiver_Set = Rx_Set;
		Transmitter_Pt= Tx_Pt;
		Receiver_Pt= Rx_Pt;
		Transmitter_Element = Rx_Ele;
		Receiver_Element = Tx_Ele;
		value=complex(0,0);
	}
	H_Item& operator+(const H_Item& rhs)
	{
		Same_Item(rhs);
		H_Item* h = new H_Item();
		h->value = this->value + rhs.value;
		return *(h);
	}
	bool Same_Item(const H_Item& rhs)
	{
		if ((this->Receiver_Set == rhs.Receiver_Set) &&
			(this->Receiver_Element == rhs.Receiver_Element) &&
			(this->Transmitter_Set == rhs.Transmitter_Set) &&
			(this->Transmitter_Element == rhs.Transmitter_Element))
		{
			return true;
		}
		else
		{
			cerr << " Unmatched Elements\n";
			return false;
		}

	}
	H_Item& SetValue(std::complex<double> v) {
		this->value = v;
		return *this;
	}
	std::complex<double> GetValue() {
		return this->value;
	}
	unsigned short GetTansmitterElement()
	{
		return this->Transmitter_Element;
	}
	unsigned short GetReceiverElement()
	{
		return this->Receiver_Element;
	}
	unsigned short GetTransmitterPt()
	{
		return this->Transmitter_Pt;
	}
	unsigned short GetReceiverPt()
	{
		return this->Receiver_Pt;
	}
	unsigned short GetTransmitterID()
	{
		return this->Transmitter_Set;
	}
	unsigned short GetReceiverID()
	{
		return this->Receiver_Set;
	}
	/// additional methods : get value with time 
	std::string toString() { return std::to_string(value.real()) + "+" + std::to_string(value.imag()); }
private:
	unsigned short Transmitter_Set;
	unsigned short Receiver_Set;
	unsigned short Transmitter_Pt;
	unsigned short Receiver_Pt;
	unsigned short Transmitter_Element;
	unsigned short Receiver_Element;
	std::complex<double> value;

};

