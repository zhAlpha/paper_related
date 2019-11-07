#include "IO.h"

CIO::CIO()
{
}

CIO::~CIO()
{
}


int CIO::loadData(string fileName, cv::Mat& matData, int matRows, int matCols, int matChns)  
{  
	
	int retVal = 0;  

	// ���ļ�  
	ifstream inFile(fileName.c_str(), ios_base::in);  
	if(!inFile.is_open())  
	{  
		cout << "��ȡ�ļ�ʧ��" << endl;  
		retVal = -1;  
		return (retVal);  
	}  

	// ��������  
	istream_iterator<double> begin(inFile);    //�� float ��ʽȡ�ļ�����������ʼָ��  
	istream_iterator<double> end;          //ȡ�ļ�������ֹλ��  
	vector<float> inData(begin,end);      //���ļ����ݱ����� std::vector ��  	

	// ����������д���  
	//copy(vec.begin(),vec.end(),ostream_iterator<double>(cout,"\t"));   

	// ����趨�ľ���ߴ��ͨ����  	
	//1.ͨ����  
	if (matChns == 0)  
	{  
		matChns = 1;  
	}  
	matRows = inData[0];
	size_t dataLength = inData.size()-1;  

	//2.������  
	if (matRows != 0 && matCols == 0)  
	{  
		matCols = dataLength / matChns / matRows;  
	}   
	else if (matCols != 0 && matRows == 0)  
	{  
		matRows = dataLength / matChns / matCols;  
	}  
	else if (matCols == 0 && matRows == 0)  
	{  
		matRows = dataLength / matChns;  
		matCols = 1;  
	}  
	//3.�����ܳ���  
	if (dataLength != (matRows * matCols * matChns))  
	{  
		cout << "��������ݳ��� ������ �趨�ľ���ߴ���ͨ����Ҫ�󣬽���Ĭ�Ϸ�ʽ�������" << endl;  
		retVal = 1;  
		matChns = 1;  
		matRows = dataLength;  
	}   	

// 	vector<double> tmp;
// 	tmp.push_back(0);
// 	tmp.push_back(1);
// 	tmp.push_back(2);
// 	cv::Mat tmpMat1 = Mat(tmp);
	//tmpMat1.create()

	inData.erase(inData.begin( ) );
	cv::Mat tmpMat = cv::Mat(inData);       //�������� std::vector ת��Ϊ cv::Mat  
	// ���ļ����ݱ������������  
	matData = tmpMat.reshape(matChns, matRows).clone();  

	return (retVal);  
}  
	

int CIO::writeData(string fileName, cv::Mat& matData)  
{  
	int retVal = 0;  

	// �������Ƿ�Ϊ��  
	if (matData.empty())  
	{  
		cout << "����Ϊ��" << endl;   
		retVal = 1;  
		return (retVal);  
	}  

	// ���ļ�  
	ofstream outFile(fileName.c_str(), ios_base::out);  //���½��򸲸Ƿ�ʽд��  
	if (!outFile.is_open())  
	{  
		cout << "���ļ�ʧ��" << endl;   
		retVal = -1;  
		return (retVal);  
	}  

	// д������  
	int num = 0;
	//outFile << matData.rows<<endl;
	for (int r = 0; r < matData.rows; r++)  
	{  
	//	outFile << num << "\t";
		for (int c = 0; c < matData.cols; c++)  
		{  
			
			float data = matData.at<float>(r,c);    //��ȡ���ݣ�at<type> - type �Ǿ���Ԫ�صľ������ݸ�ʽ  
			 outFile<< data << "\t" ;   //ÿ�������� tab ����  			
		}  
//		num++;
		outFile << endl;  //����  
	}  

	return (retVal);  
}  