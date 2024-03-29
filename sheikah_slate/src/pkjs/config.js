module.exports = [
  {
    "type": "heading",
    "defaultValue": "Sheikah Slate Configuration"
  },
  { 
    "type": "text",
    "defaultValue": "Set up your Sheikah Slate here"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Vibration"
      },
      {
        "type": "toggle",
        "messageKey": "VibrateOnDisc",
        "label": "Vibrate on bluetooth disconnect",
        "defaultValue": true
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Time and Date"
      },
      {
        "type": "toggle",
        "messageKey": "AmericanDate",
        "label": "Use American date format",
        "defaultValue": true,
        "description": "Set false for '01 Jan', true for 'Jan 01'"
      }
    ]
  },
  {
  	"type": "section",
  	"items": [
  		{
  			"type": "heading",
  			"defaultValue": "Column Text\n<img src=\" data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAQYAAAAaCAYAAABVVvJoAAAABmJLR0QAVQD/AP+aKiCkAAAACXBIWXMAAA7DAAAOwwHHb6hkAAAAB3RJTUUH5AETBQg3SGLPGQAAFm9JREFUeNrtXXtwVdXV/+1zzj3n3puECAlvJUB5VRoHQpURHVRURByoLbY6VfoSEERq+rBOQ2nK0JTpMJSpGgexjNAZ0frA2lKhhUbRBqsDMlalMIilxFpDCHne9z1nfX/4rdV97iPv9qPfZP/Dybr7rLP3b6+z93oeFBERBttgG2yDTWvGIASDbbANtsxm8cWJEydw8uRJAMDUqVMxefJkAMD+/fuRSCQAAEopsIKhX19++eUYOXIkUqkUfv/73wvzq666CkOHDgUA7NmzR+4DACLy8TBNE9dccw3C4TDOnj2LN998s8tnOo6DG2+8EQB8/QsKCnDdddcBAN59912cPn26Sz75rqdMmYIpU6YAAN5++200NDQAAMrLy1FWVgYiwr59++C6bl4+Ok2ne56HG2+8EaFQCADw4osvwjRNAMD8+fNh2zY+/vhjHD58GAAQCAQwb948BAIBNDQ04O233wYAFBYWYu7cuTAMAydPnsSJEycAAEOHDsVVV10FAL7++eY6duxYzJw5EwBQX1+PlpYWAMCkSZMwbdo0eJ6H1157DR0dHQCAz3zmMxg/fjwA4NChQzh//jwAoKKiAmPGjEEymcSBAwfgeV4WHrnWXqd7noeFCxfCsiwkk0ns3bsXpmlCKYVbbrmlx3PKdz169GjMmjULAPDBBx/g2LFjAICysjKUl5cDAF555RV0dnZ2yYflwHVdHDhwAKlUCgAwa9YsjB49GgBw4MABxONxKKUwe/ZslJaWoqOjA6+++mpOWdGxueGGG+A4DpqamvDGG29I34ULF0Iphfb2dhw8eBBKKViWhQULFgAA3n//fRw/frxP2EyYMAHTp08HD4SIiHbv3k0ACAD99re/ZTItWLBA6IFAQK6DwaBc/+UvfyEiomg0SrZtC/1vf/ub8GGaaZrSJxQKCf3SSy+l5uZmIiJ67733SClFAHz89Gfeeuut5Hme9Gf60qVL5Zk7d+4Uus7HcZycdJ2/jsFjjz0m9IMHDxIRkeu6NHPmzC75W5Yl88jkz3PVsQFAnZ2dRER09OhRoV177bUUjUaJiOj1118X+t13302pVIqIiPbs2SP0733ve4LNoUOHhK7jrV/X1tbKWKqqqoS+e/duIiJKp9O0cuVKob/88svSf+3atUI/fPgwERF1dHTQxIkTs7AxDIMsy8qSJV0mAFA8Hicios7OTt94eU719fXdyqROD4fDcv3QQw/J2Pfv3y/0J554QujLli3rlj/LQTKZpHnz5gn96NGjwmfRokUyvxMnThAR0T//+U8aMWJEFv9AIECGYRAAKigooLa2NiIiOnbsmPS95JJLKJ1OExHRP/7xD6Fffvnl8syXXnqpVzKvy8GuXbuET7emhH7i9dYdkau/67pykvC/Pb23J2PpyRj15+bj2Z+56vMbCBdOV3Pl33qLTW/7DBQeudY+Uw76ilm+dc1H7+s8BnI9u8OmP2uQD5t81zp/S785FAohlUr5Ore3tyMUCiEej+OBBx7AtGnTYJom7r33XiilEIvFxNRIJpNwXRehUAixWAzpdFr47Ny50/fwTBXKNE3Yti2DZTV73Lhx+O53vwvHceC6LgzDEJNBb4FAAJZliUoHAOl0GsFgEEopzJs3D3fccYeoq8wnnU7Dsiyhm6YJIhJVmcfKc9KxaW5uFvq6detQVlaWV1WORqNYtWpVTmwY+1gsJn+XlpYKZo7jiKlBRLBtG6ZpIhKJyDPi8bjMNZlM+rBlLBcsWIAvfOELAIAXXngBe/fuBQBZPx17IpLxeJ6HeDyOUCgEz/N8/efOnSsmV2lpqazFhg0b4LpuTnMhE5uWlhZUVlb2GBv+PRQKYdq0aaisrJRxMk4sK0opuK4r6zphwoQs3rz23GKxmMx1+fLluOKKK3w8AWDUqFEy/hUrVuCrX/0qAKCkpCRLbvQXMBQK4Wc/+5nv0Mh8F5RSCAQC8k7xffF4HOl0WubI9Egk4sNGKYVgMIjPfvazWLFihWw6OjaZ10SEqVOn5t4YGHyePAAUFxcLfcGCBZg7dy4A4Nvf/jba29tFcAGIwHJ/nhwAfOUrX+m5R9QwEI/HQUQYM2YM7rrrLgSDwS7vSaVSSKVSsrkAgGVZiMfjAIAZM2bgrrvu6vMOnwubkpISnDlzBgCwaNEizJgxIy+PtrY2rFq1SvhYlg96n+ADwMUXX5wTM37x2cfA42HB4fVgIdN5V1RUCAZnzpzB7t27fevHGzT3D4fDMmf95dT7z58/P2uMjuPgzjvv7DG+H330ESorK3PKDY+fx6JjF4vFMGHCBCxdutQ33960XOuqz3XevHn4/Oc/n99JZ1m4/fbbu5Qb0zSFf3Fxca/kkLGOxWIoLS3NKTf6IcmHXCwWw7Rp0/os8zlNCX1Hyge4Tuf++n39CpUYRtZJMxA8B7r1Z2x9vbenGHfHX/89X1/GjJ1/AzHvgcZLKTUg49HlY6DnR0R9lr/+vFP9kXlLByMcDsPzPNTW1mLfvn1QSuHo0aMIh8OIRqNyIgFAY2MjwuEw0uk01q9fj1GjRiGRSMCyLFiWhWg06lM516xZA8MwRA20LEv6m6aJZDIJwzBgWRbOnTsnJ0RnZycSiQSCwSCOHj2KHTt2AACGDx+OtWvXyiLati08uSWTSYRCISil8Otf/xrt7e0gIiQSCdmJOzs7UVhY6FMhiQi33XabaEeMTTwelygEAJw+fToLGyLCfffdB8uykE6nUVVVhbFjxyIajcopnImNTud2/Phx1NbWivZk2zYMw8BHH30kc2pubobrurAsC21tbUKPRqM+c4mx1FV0/RRmDzyrlkyvra1FXV0dPM9DXV2dyIc+zoFomdgkk0mfVhIOh33qMpuL4XAYr7/+Or75zW9CKSXmFABceumlWLFiBZRS2Lt3L/bt2yeRsi996Us+3kSEnTt34siRI1BK4ZVXXpG56prchg0bcO7cOTmRuU8ymZTn3nvvvaKSs9wQEdavX49hw4bJ2Fkr+v73v49Ro0ahsbERNTU1UEohkUjANE1YloWmpiYxJTs6OpBKpXybRTgcRltbmw8b0zThOA7279+PysrKLJm/4oorRKN77rnn8Nprr4GIcMstt+Cmm27ybwxEJAtUV1eH3/3ud1kCq6vzI0eORGNjIwzDwPPPPy8vjN5fX9xHHnlEdkDeCHSVTSkF0zSRTqfhOI68OIWFhT516qGHHgIA3HrrrT7hSiaTWQJl27bwP3HiBN555x0ZF/O3bVtU82AwKC+4riLr2OiLMn78eLz11ls+bIgIjz76qPR58MEHfS9nLmx0Ord4PO7DjO1gfYwlJSUyHt3kC4fDvtOCeetqaDAYFDpvjPwsph88eBD79+/PUq91tX4gWiY2ujnIdP2Z/FJFo1GkUik8/PDDWetXVVUl/VtaWkRuJk2alBP3Q4cOoa6uLkuG2UcAAIcPH8ZvfvMbGYO+QXH/r3/96znl5rnnnpMNPp1Ow/M82LaNBx54QF5onocuk7Ztw3VdJBIJlJSUZJlZ0WgUxcXFPmxc10U0GsWHH36In//851kyv3nzZunf1NQk2Fx55ZVdmxL98ZQPdNM97xda68+4/t1z+nfy/29Ilv2/MHf+PzU5QsrKyvD444+L2sEnYCQSQUFBAYjI53H9yU9+AiKC67pIpVIIBoNwXVdOfM/zsk6WQCAAz/NQU1ODiy66yGc+6OpTMpmUU4NVaPZ6P/7441k7OdtTpmn6VPTJkydL/46ODhQVFYl2wfyZTkR44YUXJDFHP8HZS5xKpXymxJkzZ4TOJ5VSClu3boVpmnBdV3DUHWvsKM3ERqcNHToU27Ztk8iP4zhiVjDPIUOG+KJHfJrEYjGfl9u2bRCRz5RIJBIIBAJQSvlMiTlz5ghmbGZlysSIESOk/9NPP40PPvgArusiFouhsLAQrusiEolgyJAhYtYw3XVd2Lbtozc1NfkwyNT8AoGAbz2GDx8u2EQiEYTDYSilcOzYMTz88MNQSuHjjz/2aQyWZUl/xmb06NEyVx1Xlnngk+QvbrfffjsWLVrkMyVSqRQ2b96MM2fOCE7c7rjjDixevBie5yGdTsO2bbS2tqK6uhqpVAqGYYhmwJttIBCAaZrYsmULCgsLZZ3y+QsCgYDPlBg7dqxgo5vJR44cwfbt2wHAh8358+cRCARARD5zTTaGiooKVFRU9HhHufvuu3u9C7HgL126FCNHjuz1/Xo2Yq44red5PoG68sorfepRd+3s2bMSwtM3NSKSseumRFlZWZYpoZTCPffck8WbNzLmk6kuZ24UZWVlWL58eY/HPmTIEOERCoV8gsTCp5sSjuNIf92U4OzCnrZ3330XNTU1PpWavfD6XPkQYD+TvhEahpGlPmdio6/H5MmTJTNXb3V1ddiyZYsvnMibLG+KBQUFsmFOnz79X5l+PWhf/vKXs2jpdBrPP/88Tp06lWUi5urf2NiITZs24ezZs7658pg4srZs2TLfunT1TummxGWXXYbLLrssq19paSm2bt0KAJKZyeYor4MvujGoNF34Jst/i9rNsXpdq9LpXSXZZN7TlzFeSNGSC83E6e1zZWP405/+hD/+8Y+yUHzicAKE53lYsmSJ7EbV1dUSVuRwjH7tui5WrlyJMWPG+E4pIsKmTZtEfedBe54noSf9+aFQCPfffz8cx8E777wjsfeioiJ861vfkglzdEM/eQ8cOID6+npxOrEnds+ePThy5Ih4aG+++WZRJzmRik8vHh87b3SBbmlpETo/l4iwdu1aOZHvu+8+jBo1Sn7n/pkvgu4cAoBTp07hl7/8JQzD8OGhX48YMQLLly8XU8y2bSilkEqlfKYEn2L6M1OplNBffPFFnD17Niv5S0+E0emLFy+W2gpd+1i/fj0+9alPCQ6ZSU093aAzQ3SO4/jU3Pfeew/PPPOMyBn3P3XqlGCg92enn54Dws5EdrLnm/f111+Pq6++Wpx2bHZxH9d18f7774ts6+bali1bJBLG70VHRwcikQgcx5HIVeZciQg1NTUIBoO+cQHAunXrfH87juMzs95880289NJLvsQuADh27JhgoJuOsVhMTE0dm5y1Enr+tJ5nzvnhRCT53oZhkGmaOfv3plZCKSV59Hpe93XXXSd1AnqOfG9rJdauXZuz9uEXv/gFERF5nkcbNmzoc60E58i7ruurffj73/9OREStra0+em9qJUzTlDx6PV+/t7USGzZskGfW1NTkrAfoSU59d7USA9X6UytRVVUl/Z988sluayX0e3UZ5noRIqLFixd3W4uRq1ZC52/btqylbdvU0NBAREQNDQ05cbdtW96vgaqV2Lx5s/R/9NFHhf7kk092XSvRE5W6rypRvvx+/e/MisSBUL96kqh1oZs6vYkI9Gd9LsRIRE+Sdf6TYxyIOpKe3DdQJm5v32mfj8G2bXieh3vuuQcVFRUwDAM/+tGP0NDQgGQy6Uv2aGxsFIfRunXrMGnSJEQiEVRWVgpdV4137Nghqhx7+bkk1XEcdHZ2wnEcBAIBfPjhh1i/fj2AT1KJ2WNcUlIi9QPBYDCr1sI0TV8Slh59YM83q4FMZw8tEaG5uVkw0FVRpZTMSS+z/s53viP1AOwAUkph+/btsCwLnudJpEAphSeeeELU38x4tO58A4Bhw4YJZm1tbSgqKpLy6p/+9KdQSqGxsVFqPdra2iTKkJngxHPVzazZs2dj586dUEqhqakJw4cPB/BJXJwTpZjOcXF2hmU6jjOxGehm23bOBCfbtjF+/HhUVVXJvDmCdtFFF0n/8ePHi9yMGzcuizc7Cq+55hoYhoHa2lq89dZbWXJw5513YsmSJSAitLa2ilMzkUiI405/LsuNUgrV1dVSks71RLrTOhwOy3pHo1EYhoFgMIjTp0+jurpaIhqZCU62bUuZfCY25eXlqKyslEQtTrbS1+/Tn/60YDNx4sTcGwML5vz587Fw4UIAwK5du8TjqocIOcGJwzjTp09HIpFAZWWl8NE9tFxk0pP217/+FT/4wQ/khWPwpk6d6iv00BuHwvQkLP1l4wIf3kSYrhfDlJSUCF330Or2Fy+KUipnPYBSCt/4xjdyRg2+9rWv5Z2zz777XwHOhdkbb7yBH//4x7IGHGkoLi72Jdzkikrom9H1118/YC9uJjYD3ZLJpG899AKj8vLybmVrzpw5mDNnTpdjnzt3rtSmvPrqq/jzn/+cJQd6xmRPT+lkMgnTNLFkyZKckRT9IMg1j+PHj6O6uhrJZBIjR47MOlCSyaR88yQTm1mzZnVbK3Httdd27XzM5UXOvGa1JvMDJH0to86nymSqaVyJlunEyqUu91bt6k+Ja39UvJ6o+pkmVa4xdmWWZT5D79sT52BXTsN8/XuDSa455eOdTxvhMHWuueabX3dykw/j/oy/t7LFPHpSMp6Pzvd2JRv5sOm27LqlpQWhUAjpdBo7duxAfX09DMOQ3PxYLCYmBnvtma6fgjU1NTAMA4lEAoZhIBAI+PpbloWVK1diyJAhkvoLfJLKvHHjRoRCIbS2toqqVlRUhNWrV8vJmKvsmhOv+Is3OmDMn5NDiEhKzF3X9ZkkXD4bj8d9m+CmTZskwUs/1dj00emxWAyGYcBxHKTTadx///2++HNmafHJkyfxzDPPSAnt6tWrJXGMq1jb29tlPJFIRObKlamZZdcvv/yyVN+dP38ew4YNAwDftZ7ow3Q9eQn4pMpWz3lhzLZv344//OEPYnoUFRXJWLgPm1fpdBqrV69GSUkJGhsbsW3bNlm/Bx980Kf5ZWKj52scOXIEGzdulEQwnmtrayuKi4thGAbOnTsnyXnTp0/H5z73OR/vzLLrSCQi9KeffhrHjx8XFZ/533zzzZg5cyYSiQRqa2tFXm677TbJtclVdt3c3Ixt27ZJujTXNSSTSViWJfK8Zs0awU/HoLuya06cchwH9fX12LhxI4go57ry+80ax+zZs/+lSf6nv+BkGIbw0XlkfsEJ3Xxh6UKLSmR6kjma8N/wBaeeRCX0seeLSrB33jRNH89cX3ACQE1NTVkeduT5glM4HO42KqGPXafrc+3PF5x0/gP9BSf9a1//7i845XuP9aiE1Rt1tquv7nSn8un39UZN6snXZi4Ez3SucWZ+wamvXwAaqLn2BMve4t3bBKe+rk9mZmhv5jFQXz7qK598eOi/6djkk5O+mhJ9MZllY5gyZQqeffZZEJEkqQDA6tWrsWzZsqzyUvb4E5GoIkopPPXUU5KkpKexslqsl1pzIg57btlDPHToUDz77LNinnB/vcqOn62UwrBhw6S/7iwqLy8XOqtOwCcfbWH6JZdcIvSrr75a6Lr3eubMmYLNxRdfLHP94Q9/KE5PrhFhIeYqN6br0ZjMqMSuXbskX53pI0aMEMx4/uxw1OfKm2xZWZnQdRNl9OjRQtdrAPJd65EcpmeuvZ5Se8MNN2DGjBm+tdT7Z9I5gUmPDAWDQfzqV7+SiI3uSHvqqafEwcpzHTNmjGCjy4Q+dp2u1wzoqdLjxo0TbHSP/Be/+EXcdNNNooKzOaDz1zFYs2YNVq1aJbLLbfny5eLQZBM4HA5j69at4phkmUin05IyTkQ+pzLPVfd3FBQUCGZ6qvvEiROlv76uLJNdrb3vq2WD/6/EYBtsgy2zDf6/EoNtsA22rPY/zDhrxmc8qDAAAAAASUVORK5CYII=\">"
  		},
			{
				"type": "input",
				"messageKey": "LeftColumnText",
				"defaultValue": "",
				"label": "Left Column Text",
				"attributes": {
					"limit": 11,
					"type": "text"
				}
			},
			{
				"type": "input",
				"messageKey": "RightColumnText",
				"defaultValue": "",
				"label": "Right Column Text",
				"description": "11 characters max. Leave blank for random letters.",
				"attributes": {
					"limit": 11,
					"type": "text"
				}
			}
  	]
  },
  {
  	"type": "section",
  	"items": [
  		{
  			"type": "heading",
  			"defaultValue": "Runes"
  		},
  		{
  			"type": "checkboxgroup",
  			"messageKey": "RunesToChoose",
  			"label": "Select which runes to display:",
  			"defaultValue": [true, true, true, true, true, true, true],
  			"options": [
  				"<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGgAAABoCAYAAAAdHLWhAAAABmJLR0QA/wCqAADnyKRFAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH4wweDQkhvEE2ZQAAAhNJREFUeNrtnduOwyAMBWOU//9l9mmlKK1SaG1s45mnXalNKMPhkjT0OAAAAAAAAAAAAAAAAGBnhCoYoPf+uSZFEBRRjLEoBGnKMZCEIG05ypIQZCFHUdKJkR8rXFMoCfoyPSNJ+OW9DzSsxOZM3brvrfP6Gq2Z1OhxRMSiuztTCZmppPv7jRaS9RI0I6b3/lLx1/+vx/r/O5moM21aniTdZb0TlUSWpJajNdPSWsuMjJNpBFmuHz5Vyuy5y02zjRd3R+/98RyJxiHZSoz1FYDZ4yg0BNlezui6yaOrDdPFRZATIbUhBUWSs6osimNcIzlx5cS8koCYRYJ2Tc/iKXorLSfBeoj7QcEltXLpMbheludKQqZxZ1SKs9C6XdxoYxIRz4TVHoNmEu8kSVw+bNYu0OFmH7O4pwYX4HsNjfTE/swkaFbEFlcSAEFVUtTUC884RIJ2nhQgiDGoCIvGIcka/d3FkKAkDRJBwSXRxQXv8kgQszhAEILAbYjLOPWstCYiQXRxgCDGIMYhj/GHBJVKUKUU8dVfQFDJLq5CN7f4hp3NyXj8kS6OLo4UuafHVtBOkniAC3wStEOKnB8wXnPyrJICPP1dazuyZHLWCsokKdC+CT4FiSoq4IYWe24qu4kcX0FRRAXfqydG4SJtNosgZ1nJfhogbmG1RSX9cY08hbbYLR4AAAAAAAAAAAAAAADAmT/y8fNhqk8jUQAAAABJRU5ErkJggg==\">",
  				"<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGgAAABoCAYAAAAdHLWhAAAABmJLR0QAAAAAAFXiQh4EAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH4wwfAzEHy/FFDAAAAWBJREFUeNrt3MtugzAQQFGm6v//srvtohWPAJ4Zn7OtqoBvTLCJsm0AAAAAAGxR+ujHGPtnGCFQxjBNQsUScQpHimXiFI0US8UpGOm7x63OHwN+Z1Az6OLsOTITPvnfBL6sNAR677LWcB1kBgmEQAIh0FML1+LrITPIQvWFGXN2J8FWT9LLnRlUIITd7MSRPA9KHMkT1aSh7MUhkHXQYrfShS570T5G8WgxZYB/D0bmReaZ43wocEx59++dTMYZNOmOcU6gqyczayfhyXNKG+jTkzrzOm+8RttAT767356l7QPd9Rkx6zNu6UBHBmGMsfv3Yrfq9QJdGYyMx3SQ7yQkV3svbm/wGzxprb9Z+l+EJo/BfSfBDEIggRAIgQRCIIEQCIEEQiAEEgiBBEIgBBIIgQRCIAQSCIEQSCAEEgiBEEggBBIIgRBIIARCIIG4xZzfLG05krV/QB0AAAAAILUfPUaWdd97WiwAAAAASUVORK5CYII=\">",
  				"<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGgAAABoCAYAAAAdHLWhAAAABmJLR0QA/wCqAADnyKRFAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH4wwfATgJ/g8HLAAAAnBJREFUeNrtnVuSwyAMBCPdcU+ZQ2YPsLUJdnjMSD3fLhe4GVkIbB4PhBBCjno9fl7ufYgOcOLxDACJO8cVUnSA4wwpusBxhRSd4DhCim5w3CBFRzhOkKIrHBdI0RmOA6T2DlKH1Pod5ACpbRbnAimpEOCgqXDePcSKKXc4Omc2JLK4zWGtUtknHOHMgkQlYUNWdhcStbiNKfNVSFSzD8xnRiGxHnRwsvkJEiuqVALqAVqxNaoSpKgGpxqkqAinEqQADoCA4wIIOMKAgCMMCDjCgIAjDAg43yuBox1BAjh74NxtbwBnn3PutDuAszeCXG2/zb64Ku+cq4M4XNxTLSEY7U8A59wAHemXfIirnEqPbQ0Tdk+Hec6nfgZwNPr/X38lQ5zPpsLn8iQrgaMNKRTs7QpnR7hLnHOmQjB6n1BwT6XC5+zty4lzrg/IFU6yyuIcwtpMSO+uT9xzP5TPgPTpupzd6OrOmQmpRC3OIWW+A2nUYccAqYa3FYXPv6nzeN9x0MTwPQKp9IqqQyVgdgoOoAWJz8z7JXDWZKWz7pvA0b5/Akc7U03gaE8jEjjac7wEjvYE/Oh60M5qguu25MQ5unCOA9rx4Nw39Gfl0V3ha4tUbBRwvkwSVj2AGR3etaC4a5DKbf292/GdK707I4j93uzdS/C7w7ssIEWdePfaxPyOcKYA6gDpZNbKiqr4lMLmI+KOcKYCqgZJZTJOiBOGM91BFVykVsay/ZlSBzjLADlCankClwuk9idwqYLigCdhSBzwJAqK84OEIXF+kCAs978ClzqBqxIYOUDfAqv+/2yEEEIIIYQQQgghhNBa/QJibXh9JmaGRgAAAABJRU5ErkJggg==\">",
  				"<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGgAAABoCAYAAAAdHLWhAAAABmJLR0QAAACqAAAtrGPJAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH5AEBFS0PbqWbBAAAAbpJREFUeNrt3UGWgyAQRVHL4xZ7lVmkGWXYsW1Bq+C+sYnI4wuIIcsCAAAAoDFRteD7/rOfutB4BUGJhIwiLGYTU01UzCqmiqiYXUx2UUFObklBTG5RQU5uSUFObklBTm5JQU5uSesCTxJGSM9TKYrqco4q7IlztmQbvSV/jivb71VMz39bcIYyDJ2gq5VSMU1RJT2tW2zGMpUdZveoCAt2jVpq74rMXr51tuRUS5InCclZZ05PhRSlvL8/VWEZy+sW5xYHgggCQSCIIBBEEAgCQQSBIBBEEAgiCAThN5ot1Vb/1ULzim20DB7k5JYU5OSWpA8ySABBBIEgEEQQCJqNrfoFPLFPAkENZ+jV90nYRhUziqh1Bjmtv0OCGvQ1346PeEWZzQSvfsEdF/qtso/Of+WzGVJvmK0Pei49R8dU6I8kiKDcIy47jWBeQX9p/VX/N0iCTFTvTdGZiaoEgSCCQNCVpwCVziFBEjRmiiosOUgQQTlbugW7jpPSmcpc6hbXomKrvTRS7lHPp4LPtkyvXSUV5cXFCSazRnEgiCAQRBAIAkEE4T5sptSzcjNspkRSPzkAAAAAuvAGOKThczNlQHgAAAAASUVORK5CYII=\">",
  				"<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGgAAABoCAYAAAAdHLWhAAAABmJLR0QA/wCqAADnyKRFAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH4wwfATEdNRdoGAAAAttJREFUeNrtndGSwyAIRYOTb+xH9iezrzudTmMEBPTcx51tBC4goibHAQAAAAAA6kFWUOJ9Xde3v79EBIKSkrMKSY0kAkEAgiAIBOGsVghoJ33LZxFBX6q0u6pt1rOIoA5D90ZABSJKroNmGTZzqqNIIIJyR0/2KCLFJU9xJfpUXkRVKLPLNBKtSarSRC3V6bUiqVKHW6KMqjHSKFEeY3qTLZEeP5Mkz7E8SSrZSfhvFDbsQF2C3td1Ve5zzZh/tfZpmsEhqo8YjW2atWCQY2uDZi3ErtF0p/eoTVoVT9opalTrIEthVlkHecpx7uKtT3dhs0AiPeqJsSKbpZE9QInw5icCe89lM2TQRK063L2Ez7KjGkmOCUFWxuztrc0iylKncIIivP5pszRCtrAiIQMxvWM//f9sREkVckbniOg5LmwOyuKJmv2gCtHUspPjNV4VHaZG0EtELMvW3meN/MZah9EImkJQ5EQdWaCEEqTN/5WI0uqRspOwytUQrR7aKu6MUmg1eC2IzRaqo8SsEkGWNjEnyDpFzm7P/BovOiO0Fb13pZSc/uCipwG55Z3YkFWKGY7+QpBPIZHxmVsS5GnICiS1XcmpQhIL1dUXqp8GfirUagRp7fGJ0ytl7NaT83I0thsMoijldgMbdsk37NjynlNslKm8qh670pLUZg0UUequoAMHF5M7F0d/k0c+h+eTp2SunzjKscTheS5wBXYSLITnCmTgXMMlYgeCot+TEOHNvCdhwiRetbteJsWNyjJjDE99m7en7wBPXc17cS8R2fEA/Z3eU69AEjXzbNAsBNk1anqjSWObk4jJHU0c/U2Osu/N7i19q58y4tMAgXqkICgialaaO/k8DQTlI6cSSXwi7eATaanJyU4SEXTwHVWwKkF3nt3j+RbPoJPgnJKyHOlaMsV9kqHxeMtnUSQYFRJ8ww5AEAQBCAKbFgm/CgW25AEAAAAAQAz+AJhOnWw84SWzAAAAAElFTkSuQmCC\">",
  				"<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGgAAABoCAYAAAAdHLWhAAAABmJLR0QAAACqAAAtrGPJAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH5AEBFyERO5s9BQAAAhNJREFUeNrtndFygyAQRYXhF8lHlo+0T53ptE1VRLgXznlODNnjLqtgsm0AAAAAAAAAAAAAAAAAAACWBMlR7ds+KBoBQapyRCVFigglzid7BLMoDQloEJ37BIkyZ7tK9oiNpf8c9Ff2KMkRG1O0P9spcQtmj9DYUrNAg2abnT/q3ldeRqVy4AkZR8gB8TsJVtkzeC6KQ7LHsQscNObuGVSycYs+QFJYJgNMm42AHG1JATnaklgPos0GBE1Mcv8Cufxfz63betcm4UiKvKwLTYKVoFoxaqJy2UJ5TVTiWon5eTyH8hdXk9Pr2EsI6hFAdUlxZTkOktIMct7NJVeOk8sWFOek5CrnTDC/v+bMcRUlWd5JqAmi6wVrdMueO4E+8161+SjOnjnumRRdsqdlYI+OpZRFcZXMcc0klhsQ5HmhqDIm+Qx6shRxsxQQhCBAECAIQY7tLiuqxu2uypgocWSQZilyKG9SgnreYXbajWpV4lpIcskcSUFPr3g+vWJLk3BDklvmfCG3q6fkbT+7A+forG+1fQtBlZJaZofq0oNsiesZMOV1Iek5qEfg1BftWFGlSWgXyFke4JpOUCtRjtt/LR8ivrIp3v0hYvunvN0FTHknYSUQhCBAEILAQxC/l32bq9dw8ekPgHuxS70+CJiDEAQIgl99Wc0cxH823OLsb8VVC0JSHzkAAAAAAAAAAADQj0//DsSQ6vFF0wAAAABJRU5ErkJggg==\">",
  				"<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGkAAABoCAYAAADy3t6fAAAABmJLR0QAAACqAAAtrGPJAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH5AEMFDQ1wAFZRAAAAhpJREFUeNrtm1tSwzAMRSUPW6SLhEWGL5gOjzYkUnRln/PJMKmvT/xSXTMAAAAAAAAAAAAAAAAAAAAAAAAAAAAA6IZXN2B7s+1Ho2717ULSH3KQJSJpjxxkFUo6IghRF0o6I2h1Ud5F0MqiRrcGRwpnJCV36kojanRt+EojanRu/CqifIZOnH3q81ne9AxRKuvpmOVti+5Qpal0zDQtRHVspqAjI34qSREdrCZoqjVJfvE/sWa2PcyuIugSSauLith1SlTB74PMJDTqWCAzkmYTFXlu88yOPxOss6jog7WrCJpFVEblo7TmteemUCdRWTVEicLkp4i/QnYQlVnkbVM9vlqUUmV9urLQbIKQ1ECQmdmLwvno/v8qO+nZZ1fduvUqOf8JWv0Nb/Wt26Em6Pszqnd2Rz8/9K5h5x1Y9khSuXU7EJSbJ+I5A0H5ec4+r8UW3G/m/Koie5v9uv34nO3dt72Crhq1348D0XmOvmjpI+m3QI/+/ixU9Yg6k0dyunvW8KPBqkRl5ZliTbpKlOoGqHXtbpXNxEv3ANGiFEcTVfAGpEp6ti3duw2XOeQW5RlVwboJqswTMp9nX++6XIRYHtakVdYkt/DLgLVVBbE8cY15M9ss4PsXM7ebwOsrlMeVgskIEsvjKsHkBAnl8axgZvvCfc3XioJE8vgV4R6iLGf2PAAAAAAAAAAAAAAAAAAAAAAAAAAAFXwA5Bb2P0ED/BMAAAAASUVORK5CYII=\">"
  			]
  		},
  		{
				"type": "slider",
				"messageKey": "RuneChangeRate",
				"label": "Rune update rate (in minutes):",
				"defaultValue": "60",
				"description": "Set to 0 to keep the same rune.",
				"min": 0,
				"max": 60,
				"step": 1
			}
  	]
  },
  {
  	"type": "section",
  	"items": [
  		{
  			"type": "heading",
  			"defaultValue": "Weather<img src=\" data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAJAAAAAYCAYAAAAVpXQNAAAABmJLR0QAVQD/AP+aKiCkAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH5AETBgM612HUNgAAAk5JREFUaN7tWtuWgyAMTDz+IvuR8pHsQ6ulGC6BgNGSpz3WcEmGzAQXYNq0UWacA+PcDMS1OVCVgIUDHgBwAOBGgMg457QF6+pE7nNqisvCeNdF/u6aHI0gyiVSM/ClbZ108DGLiJMSefHAgKLCAcjJwoFDXyuQh9hcvQOXm4/y83383zlrL/GTekcSQAsBALdT1NfzDcBaRGsRYSPBQ/tV6hyLiKkgPZkmavfG9WsFD0Vhoc45wGICVNjta4KzH1PnxE5x6oSHfleL33DsmvXVVOArD9O6Uw5JYRZPwDkW/X5uLaIxMhSWE6U1yaDAmAp4bq7QX4pi93G4IMxRam99uPhJ91/iLKLGb8RcVHBLq0KuvKcothVIhMZ0pUkuXROnaqXGjE+2QbT6EJUK4U9PZ1ASoFwlahHBkhWhJNESlbl27Mvb+NgpGsHrMdrQ1NL3WqNUF7dqAo9PMb1BJKljcutsEdNX5aO2C1PRqo7urjQnuEXwjzCM3Oe8FlWgg3b9w90MV3/4SQ7nkqpUPbVEq6aiuj/Jm/TairxQ4OEGpse3q/2yMAWWJ14mUpekqSuFnG/vQ5SkMGPcq8IAcZH4eU4FIfoZ5GkU05uqcvumKlEtG9TEOLxIRK8KvQZ7t+fBzfPx/P322U8IPClxLQkqbQCtuRtriXPt/ldvgEMX7cXmq4pEdE4AvrPfgOC2dmx3Bk9rHFqre5OoG9EhaU40Z3/Snxe0xGKBm5hmDVSiU56q3TgAwprKJRHAOySgtFP6aZv/VH8Pupw27Tb2D3I7Rs6TLBZ5AAAAAElFTkSuQmCC\">"
  		},
  		{
				"type": "slider",
				"label": "Weather update rate (in minutes):",
				"messageKey": "WeatherCheckRate",
				"defaultValue": "30",
				"min": 15,
				"max": 120,
				"step": 15
			},
			{
				"type": "toggle",
				"messageKey": "UseCurrentLocation",
				"label": "Use current location",
				"defaultValue": true
			},
			{
				"type": "input",
				"messageKey": "Latitude",
				"defaultValue": "",
				"label": "Latitude",
				"attributes": {
					"placeholder": "eg: 42.36",
					"type": "number"
				}
			},
			{
				"type": "input",
				"messageKey": "Longitude",
				"defaultValue": "",
				"label": "Longitude",
				"attributes": {
					"placeholder": "eg: -71.10",
					"type": "number"
				}
			},
			{
				"type": "toggle",
				"messageKey": "TemperatureMetric",
				"label": "Use metric units for temperature",
				"defaultValue": false,
				"description": "Set false for Fahrenheit, true for Celsius"
			},
			{
				"type": "input",
				"messageKey": "Temperature0",
				"defaultValue": "30",
				"label": "What temperature is \"very cold\"? <img src=\" data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAUCAYAAACXtf2DAAAABmJLR0QAVQD/AP+aKiCkAAAACXBIWXMAAC4jAAAuIwF4pT92AAAAB3RJTUUH5AETBBMv8/r24gAAAX1JREFUOMu1VUtqwzAQfTaB4Cxyg+wKPoWvUH8yq6Y5QaDBJykp5ARxvIpM6BV8g6676w28SDClqItYQpLlTxYZGNDIo6eZJz3ZAcDxQJuMSSrrKwAgmHpyLOIhc4eAVcCujYnovg3K+oo0z7BbrXurKxgDEWF7PHQW4phnYFKgxrvVGoskQrJcWr/baNM6SPOs1ckYnvsw0HTAAfA0z3hZXzUnIk5EXM0DwP04tOYDMPNvAwEmxuqCPhd5aZ5psbYBEQ1V0euiS7NzANwFgEUSoeugx9r2eNBigek0bbUW2A53f6nkeDObDxYVTL2bklWwLtGYtyPNM7y/vGpXGABOp1P7qVB3LxhDkynn/DjEU/SsLTRjQUmpUBVMvX6K/DjEm8GtsO/zp9ZBL0UFY1KdNr5tpoLbaBVMuADwU5zlZMEYvv5+teSP1Rqb2VxzW7WSXgUT5n3eXyrpQjxDLhStCrWlZFUo+0s1WmS29danQlRyL7CtGzV2Hv3L/AcDVX35XynvCwAAAABJRU5ErkJggg==\" alt=\"wtf\">",
				"attributes": {
					"placeholder": "eg: 30",
					"type": "number"
				}
			},
			{
				"type": "input",
				"messageKey": "Temperature1",
				"defaultValue": "50",
				"label": "What temperature is \"cold\"? <img src=\" data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAUCAYAAACXtf2DAAAABmJLR0QAVQD/AP+aKiCkAAAACXBIWXMAAC4jAAAuIwF4pT92AAAAB3RJTUUH5AETBBQG/gn4SQAAAjdJREFUOMu1lc9rE0EUxz9rK/5YcBEE/wFhIVDsKSCIVD2VYjZLhwRs0UPxVPAg6EFy8LDmoAcP0lOoyEoOjUuTTXr10ovgSSmkSfXWk9A9bGArQut4iLvuJtukKH3whXnzZr/feW/mzSqA5ARt8jiLrMAHoKRq0Tj0/0sgJPt8fymai4+twKekauimQbfupnKcOopYNw1KqpYgHLQwNi3mE5mNFLACH89tMTVxemz6juMghOCw3sRzW6kiCYFi1cZzW+yuNwAQQuA4zrEOc3e9gee2KFbtxPwE8Cx0DuQvzna/ctN+w6Gi0Nvu0G63yWQykVC73Y4ghEiQ9bY7vLeeo5sGXqcbzUtAWoEvddOQK/u9BHTTkOGaNAghIgDSr5WlFfhRXAFksWozlTcAuKgoQ+l/azR5dXdxZIkKuSyVxTwAtVvX2XE3eLn0AuXP7oc+SBNaPn9hLDnAh58HeLMzPLh0I/2aHkW2st+LELda81PCv31mku/nrgL0M4gHdbNfqrBxdNPgYfXd2LIVctlUsaESbTX6xGsL94Z2PyrL1YU7/attXAPg9dwyJVUbfirCw15L2fGVfC7hxy0kPtZTES9VaIO3KK088UO+/OPLX4GwLFsNl5KqUVI1psV8aklCDJpWeIrjfgTAm51hx91INhogddOQVuBLK/BlsWqPbLA46m8fSb9WloVcNmraWLw/KFbtiHxc96ahkMtKv1aWlb1N+Xj1ybBAivI/obK3mfCVk/5l/gZzVlCMkxd8ngAAAABJRU5ErkJggg==\">",
				"attributes": {
					"placeholder": "eg: 50",
					"type": "number"
				}
			},
			{
				"type": "input",
				"messageKey": "Temperature2",
				"defaultValue": "70",
				"label": "What temperature is \"comfortable\"? <img src=\" data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAUCAYAAACXtf2DAAAABmJLR0QAVQD/AP+aKiCkAAAACXBIWXMAAC4jAAAuIwF4pT92AAAAB3RJTUUH5AETBBQO8NJwewAAAZdJREFUOMu1Vb9Lw0AYfS2dWjSL4D8gdBKcAoKLLm5Jq+FEqaOTk46lY8jq5FQQKVUxRJvmD3AShE5CJ6F/gssJ6SJyDnLXu1wSk6EffJDvfrz3vneXpAKAYYlRK7LIcRwAQBAE4pnX/0X1P2AZMIu4NAEHTlO4O7gpJaRaRtX1/EshSVqWtreaB57VRZHzKnQGciSJkuqz1gkCN6aY/nynKs7qIo2U+h6o76nXtNm2AQCnwwEAoNcwULYzYpkKMLFM+NHkr4Mt51DZ5MZUkBYJYpnod1rK2PHBzsKizZYO9jEaFybwo4k2tldfW1gkW5Kl/OJ+qNVXJx1Rnw3DVLIat4THNByndrDRsnLr/ZV1AEBfOgeDdPVvEbfrMTE+CyMFdBZG6v23t7PfZK5ajqRVsh3Jmlimtv9l/rkgeA+ehD29hoFew9BuFgCc11dFJsMgXQTjN1E/PL+KZ8az2baZG1PmxpQd3Q2YPJeXo9tLRn2PEctkABj1PXleB2+27cLgPIllMup7CpFCAKCU6rxu5Lqy7F/mL8rh6SiUmCE/AAAAAElFTkSuQmCC\">",
				"attributes": {
					"placeholder": "eg: 70",
					"type": "number"
				}
			},
			{
				"type": "input",
				"messageKey": "Temperature3",
				"defaultValue": "85",
				"label": "What temperature is \"hot\"? <img src=\" data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAUCAYAAACXtf2DAAAABmJLR0QAVQD/AP+aKiCkAAAACXBIWXMAAC4jAAAuIwF4pT92AAAAB3RJTUUH5AETBBQUDbCJAQAAAihJREFUOMu1VT1oFEEU/laCYg6yhYWVVoGr/KkWBAtBG5Hs3sXHGnMxiCmv8srjqnBsayGpNHAkuYQsw+3tGe6qoIIgWgiaKhCusLMQMiEXCQTHYp3N7uxuciJ58ODNvOH73vvezqwGQOAMbWSYQ9x1AAC6XQ1juf4vAgk2534J96Ixdx3odhW2acDtfE7FOJcFbJsGdLsaA1RN5h5P3o51diIBdx2wbh+/z189tX3GGIgIzY3vYN1+KkmMwGtUwLp99PZ3AQBEBMbYUMPs7e+CdfvwGpXsGay1PmRWLomihESEK5MFjBdMvJ19FpA8fR2biSY/U+46MNY+YdvzQUQJ4DR7vrqC8YIZrsujY7EvLuyAiLB5eIQnK0sAgFpOP1USFfz91L3YDBZLE5hrvglmMG1dx8/7d8JkfcCRL1pDg++0O3g1U4idIevW8ZDvXhjBj4s3Yge2PT8BvHCwh4WDvQT4i+mZzGI09amQlasEatUquG0aAJC4cBoAwV0HLx+UAQBb7QB4vTSbqF618uhYTPOoNHLQiafiWiHoYF3Z32l3EtKkaZ560TYPj3D511ekSSVN1Tm6lvJkEqz633Cp9w5bbR+1nI5aTsdNepgqiXTVdLsK5n88vj+RWEjPFy1RH3BRH3DxqLkkormT3GtUBHcdYZuG+DvTaD4IiEi0ludFfcBFvmgNDS7dNg3BXUdw1xGLpYkkAQDRWp7/Z2DVleqFdta/zD+LVyin5idosgAAAABJRU5ErkJggg==\">",
				"attributes": {
					"placeholder": "eg: 85",
					"type": "number"
				}
			},
			{
				"type": "input",
				"messageKey": "Temperature4",
				"defaultValue": "100",
				"label": "What temperature is \"very hot\"? <img src=\" data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAUCAYAAACXtf2DAAAABmJLR0QAVQD/AP+aKiCkAAAACXBIWXMAAC4jAAAuIwF4pT92AAAAB3RJTUUH5AETBBQa6gikBgAAAalJREFUOMu1VT1rwkAYfhI6FekiZMiBdBBK107+gQ4GtCldpHbTLRDqLykEsulUI1IoBKU69B+00F/QoQhmEFwcXK9L3+slly8HHzjIXe6e97nnfd9EA8BxRJyU2RS5DgDA9HzxTPMi6EXEMmFWYMtghwWIXAejbgv9aZirbrldwTIYhh07U4iepapZrWGxWcfeWQbDcrsS814wx7BjK2czA4y6LSVYGZ/zOAqTbBkMjz+feJl9AAAWwVqsJ8noVpbBxO01KtPIddCfhlhs1gdVCu1dblfoBfNYxYkAlCiZVFZR5pYAYhwkVgeAu+srRVWlwUr7XmnEBcqcOlVMEuS5DH+/E6NoL3FqyU8FXTdpz2AyRt1ui/l3OMPT/UPhOQ0Al5NKdd4L5or6JJzTM6U8ZTdMz1cbrVmtpVr2Hc5SLbu4vck9p8uq06wiyHbIcINnDCbj1M+ICPD6/iUWTc+H6flKZZElNGTU7TZMz48JJc5YkuV+oMbJQzIvb+eXolHlBuV/zcYj1+GR63DLYJzWi8ZgMub+fpd3/n/zqNsqTZw1khzasX+Zvx3u9ZLKxa+YAAAAAElFTkSuQmCC\">",
				"attributes": {
					"placeholder": "eg: 100",
					"type": "number"
				}
			},
  	]
  },
  {
  	"type": "submit",
  	"defaultValue": "<img src=\" data:image/png;base64,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\"><br>Submit"
  }
];
