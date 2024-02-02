 	QFile file("D:/17.json");
 	file.open(QIODevice::ReadOnly);
 	QByteArray ba = file.readAll();
 	file.close();
	
 	QJsonParseError errPar;
 	QJsonDocument doc = QJsonDocument::fromJson(ba, &errPar);
 	QString errstr = errPar.errorString();
 	QJsonObject obj = doc.object();
	
	QStringList keys = obj.keys();
	for (const QString& k : keys)
	{
		const QJsonValue& jsonVal = obj.value(k);
		if (jsonVal.isNull())
		{
			ret[key] = "null";
		}
		else if (jsonVal.isUndefined())
		{
			ret[key] = "undef";
		}
		else if (jsonVal.isBool())
		{
			bool val = jsonVal.toBool();
			ret[key] = val;
		}
		else ...
	}
	
	Object
	Array
	single-values
	
 	// #todo
	QMap<QString, QVariant> maps = extractJsonObject("", obj);

// output
// ActualValues_Camwares_0_ID = 6
// ActualValues_Camwares_0_Client_Network_IPAddress = 127.0.0.1
// ActualValues_Camwares_0_Client_Network_Port = 31200
// ...
// ActualValues_Camwares_0_Name = Left_Camware
// ActualValues_Flaps_0_Axes_Axis1 = 108
